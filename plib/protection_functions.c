
#include "protection_functions.h"
#include "math.h"

//function-1,2,3
//count  has to be initialized and supplied as different in each invocation



int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,long *count){

	int out;

	out=mem;

	if (input==1 && mem==0 )
	{
		*count=*count+1;

		if ((*count)==qual_sample)
		{
			out = 1;
			*count = 0;
		}

	}
	
	else{*count=0;}

	if (input==0){out = 0; *count=0;}

	return out;

}
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,long *count){

	int out;

	out=mem;

	if (input==0 && mem==1 )
	{
		*count=*count+1;

		if ((*count)==qual_sample)
		{
			out = 0;
			*count = 0;
		}

	}
	
	else{*count=0;}

	if (input==1){out = 1; *count=0;}

	return out;

}
int on_off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,long *count){

	int out;

	out=mem;

	if (input^mem )
	{
		*count=*count+1;

		if ((*count)==qual_sample)
		{
			out = input;
			*count = 0;
		}

	}
	
	else{*count=0;}

	
	return out;

}


//function-4
// Definite TOC

int fc50(struct fc50_inputParameters fc50_in, struct fc50_outputParameters *fc50_out, int enable ){


	if (enable)
	{

		if (fc50_in.rms > fc50_in.level)
		{
			fc50_out->initial_pick_up = 1;
		}
		if (fc50_in.rms < fc50_in.level * fc50_in.dropout_ratio)
		{
			fc50_out->initial_pick_up = 0;
		}

		fc50_out->pick_up = off_delay(fc50_out->initial_pick_up, fc50_out->pick_up, fc50_in.dropout_time*fs, &(fc50_out->dropout_counter));

		fc50_out->trip = on_delay(fc50_out->pick_up, fc50_out->trip, fc50_in.delay*fs, &(fc50_out->trip_counter));

		if (fc50_out->trip == 1)
		{
			fc50_out->trip_latch = 1;
		}

	}

	return fc50_out->trip_latch;

}

//function-5
// Inverse TOC


int fc51(struct fc51_inputParameters fc51_in, struct fc51_outputParameters *fc51_out,int enable ){

	if (enable)
	{

		if (fc51_in.rms > fc51_in.level * 1.100f){

			fc51_out->pick_up = 1;
			fc51_out->time2trip = fc51_in.time_multiplier * (fc51_in.curve_data[0] / (powf((fc51_in.rms / fc51_in.level), fc51_in.curve_data[1]) - 1.0f) + fc51_in.curve_data[2]);
			

		}
		if (fc51_in.rms < fc51_in.level * 1.045f){

			fc51_out->pick_up = 0;
			fc51_out->time2trip =80000;
			
		}



		if (fc51_out->pick_up && fc51_out->trip ==0){

			fc51_out->trip_counter++;

		}else{

			fc51_out->trip_counter = 0;

		};

		if (fc51_out->trip_counter > fc51_out->time2trip * fs){

			fc51_out->trip = 1;
			fc51_out->trip_counter = 0;

		}



	}

	return fc51_out->trip ;

}

//function-6
//Undervoltage Protection
// cs trip caution...... (has to set externally by trigger of trip)



int fc27(struct fc27_inputParameters fc27_in, struct fc27_outputParameters *fc27_out,int enable ){

	if (enable){

		if (fc27_in.rms < fc27_in.level && fc27_in.cs==0 ){
		
			fc27_out->pick_up = 1;
		
		}


		if (fc27_in.rms > fc27_in.level*fc27_in.dropout_ratio || fc27_in.cs ){
		
			fc27_out->pick_up = 0;
		
		}



		if (fc27_out->pick_up && fc27_out->trip==0){

			fc27_out->trip_counter++;

		}else{

			fc27_out->trip_counter = 0;

		}



		if (fc27_out->trip_counter > fc27_in.delay*fs){

			fc27_out->trip = 1;
			fc27_out->trip_counter = 0;

		}

	
	}

	return fc27_out->trip;

}


// function-7
// Overvoltage Protection



int fc59(struct fc59_inputParameters fc59_in, struct fc59_outputParameters *fc59_out,int enable ){

	if (enable){

		if (fc59_in.rms > fc59_in.level ){
		
			fc59_out->pick_up = 1;
		
		}


		if (fc59_in.rms < fc59_in.level*fc59_in.dropout_ratio ){
		
			fc59_out->pick_up = 0;
		
		}


		if (fc59_out->pick_up && fc59_out->trip==0){

			fc59_out->trip_counter++;

		}else{

			fc59_out->trip_counter = 0;

		}



		if (fc59_out->trip_counter > fc59_in.delay*fs){

			fc59_out->trip = 1;
			fc59_out->trip_counter = 0;

		}

	
	}

	return fc59_out->trip;

}


// function-8
// Definite TOC Negative Seq. Protection

int fc46d(struct fc46d_inputParameters fc46d_in, struct fc46d_outputParameters *fc46d_out, int enable ){


	if (enable && (fc46d_in.rms>0.1f*fc46d_in.level && fc46d_in.rms<10.0f*fc46d_in.level  ))
	{

		if (fc46d_in.rms > fc46d_in.level)
		{
			fc46d_out->initial_pick_up = 1;
		}
		if (fc46d_in.rms < fc46d_in.level * fc46d_in.dropout_ratio)
		{
			fc46d_out->initial_pick_up = 0;
		}

		fc46d_out->pick_up = off_delay(fc46d_out->initial_pick_up, fc46d_out->pick_up, fc46d_in.dropout_time*fs, &(fc46d_out->dropout_counter));

		fc46d_out->trip = on_delay(fc46d_out->pick_up, fc46d_out->trip, fc46d_in.delay*fs, &(fc46d_out->trip_counter));

		if (fc46d_out->trip == 1)
		{
			fc46d_out->trip_latch = 1;
		}

	}

	return fc46d_out->trip_latch;

}


// function-9
// Inverse TOC Negative Seq. Protection

int fc46i(struct fc46i_inputParameters fc46i_in, struct fc46i_outputParameters *fc46i_out,int enable ){

	if (enable && (fc46i_in.rms>0.1f*fc46i_in.level && fc46i_in.rms<10.0f*fc46i_in.level  )){

		if (fc46i_in.rms > fc46i_in.level * 1.100f){

			fc46i_out->pick_up = 1;
			fc46i_out->time2trip = fc46i_in.time_multiplier * (fc46i_in.curve_data[0] / (powf((fc46i_in.rms / fc46i_in.level), fc46i_in.curve_data[1]) - 1.0f) + fc46i_in.curve_data[2]);
			

		}
		if (fc46i_in.rms < fc46i_in.level * 1.045f){

			fc46i_out->pick_up = 0;
			fc46i_out->time2trip =80000; 
			
		}



		if (fc46i_out->pick_up && fc46i_out->trip ==0){

			fc46i_out->trip_counter++;

		}else{

			fc46i_out->trip_counter = 0;

		};

		if (fc46i_out->trip_counter > fc46i_out->time2trip * fs){

			fc46i_out->trip = 1;
			fc46i_out->trip_counter = 0;

		}



	}

	return fc46i_out->trip ;

}

// function-10
// Overtempereature Protection

void fc49(struct fc49_inputParameters fc49_in, struct fc49_outputParameters *fc49_out,int enable ){

	if (enable){

		if (fc49_in.temp > fc49_in.alarm_level ){
		
			fc49_out->alarm = 1;
		
		}


		if (fc49_in.temp < fc49_in.alarm_level*fc49_in.dropout_ratio ){
		
			fc49_out->alarm = 0;
		
		}


		if (fc49_in.temp > fc49_in.trip_level ){
		
			fc49_out->trip = 1;
		
		}

	
	}


}


// function-11
// Breaker Failure Protection



// function-12
// Undercurrent Protection
// bs is CB input


int fc37(struct fc37_inputParameters fc37_in, struct fc37_outputParameters *fc37_out,int enable){

	if (enable){

		if (fc37_in.rms < fc37_in.level && fc37_in.bs ){
		
			fc37_out->pick_up = 1;
		
		}


		if (fc37_in.rms > fc37_in.level*fc37_in.dropout_ratio || fc37_in.bs==0 ){
		
			fc37_out->pick_up = 0;
		
		}



		if (fc37_out->pick_up && fc37_out->trip==0){

			fc37_out->trip_counter++;

		}else{

			fc37_out->trip_counter = 0;

		}



		if (fc37_out->trip_counter > fc37_in.delay*fs){

			fc37_out->trip = 1;
			fc37_out->trip_counter = 0;

		}

	
	}

	return fc37_out->trip;

}

// Function 14
// Filter Unbalance Protection-Alarm Stage
// caution : vectoral difference has to be used


int fcUNBd(struct fcUNBd_inputParameters fcUNBd_in, struct fcUNBd_outputParameters *fcUNBd_out,int enable ){

	if (enable){

		if (fcUNBd_in.rms > fcUNBd_in.level ){
		
			fcUNBd_out->pick_up = 1;
		
		}


		if (fcUNBd_in.rms < fcUNBd_in.level*fcUNBd_in.dropout_ratio ){
		
			fcUNBd_out->pick_up = 0;
		
		}


		if (fcUNBd_out->pick_up && fcUNBd_out->trip==0){

			fcUNBd_out->trip_counter++;

		}else{

			fcUNBd_out->trip_counter = 0;

		}


		if (fcUNBd_out->trip_counter > fcUNBd_in.delay*fs){

			fcUNBd_out->trip = 1;
			fcUNBd_out->trip_counter = 0;

		}

	
	}

	return fcUNBd_out->trip;

}


// Function 15
// Filter Unbalance Protection-Trip Stage
// caution : vectoral difference has to be used


int fcUNBi(struct fcUNBi_inputParameters fcUNBi_in, struct fcUNBi_outputParameters *fcUNBi_out,int enable ){

	if (enable ){

		if (fcUNBi_in.rms > fcUNBi_in.level * 1.100f){

			fcUNBi_out->pick_up = 1;
			fcUNBi_out->time2trip = fcUNBi_in.time_multiplier * (fcUNBi_in.curve_data[0] / (100.0f*(fcUNBi_in.rms/fcUNBi_in.level)-97.0f)+0.02);
			

		}
		if (fcUNBi_in.rms < fcUNBi_in.level * 1.045f){

			fcUNBi_out->pick_up = 0;
			fcUNBi_out->time2trip =80000; 
			
		}



		if (fcUNBi_out->pick_up && fcUNBi_out->trip ==0){

			fcUNBi_out->trip_counter++;

		}else{

			fcUNBi_out->trip_counter = 0;

		};

		if (fcUNBi_out->trip_counter > fcUNBi_out->time2trip * fs){

			fcUNBi_out->trip = 1;
			fcUNBi_out->trip_counter = 0;

		}



	}

	return fcUNBi_out->trip ;

}



// Function 16
// Filter PVP definite



int fcPVPd(struct fcPVPd_inputParameters fcPVPd_in, struct fcPVPd_outputParameters *fcPVPd_out,int enable ){

	if (enable){

		if (fcPVPd_in.rms > fcPVPd_in.level ){
		
			fcPVPd_out->pick_up = 1;
		
		}


		if (fcPVPd_in.rms < fcPVPd_in.level*fcPVPd_in.dropout_ratio ){
		
			fcPVPd_out->pick_up = 0;
		
		}


		if (fcPVPd_out->pick_up && fcPVPd_out->trip==0){

			fcPVPd_out->trip_counter++;

		}else{

			fcPVPd_out->trip_counter = 0;

		}


		if (fcPVPd_out->trip_counter > fcPVPd_in.delay*fs){

			fcPVPd_out->trip = 1;
			fcPVPd_out->trip_counter = 0;

		}

	
	}

	return fcPVPd_out->trip;

}


// Function 17
// Filter PVP-Trip Stage



int fcPVPi(struct fcPVPi_inputParameters fcPVPi_in, struct fcPVPi_outputParameters *fcPVPi_out,int enable ){

	if (enable ){

		if (fcPVPi_in.rms > fcPVPi_in.level * 1.100f){

			fcPVPi_out->pick_up = 1;
			fcPVPi_out->time2trip = fcPVPi_in.time_multiplier * (fcPVPi_in.curve_data[0] / (100.0f*(fcPVPi_in.rms/fcPVPi_in.level)-97.0f)+0.02);
			

		}
		if (fcPVPi_in.rms < fcPVPi_in.level * 1.045f){

			fcPVPi_out->pick_up = 0;
			fcPVPi_out->time2trip =80000; 
			
		}



		if (fcPVPi_out->pick_up && fcPVPi_out->trip ==0){

			fcPVPi_out->trip_counter++;

		}else{

			fcPVPi_out->trip_counter = 0;

		};

		if (fcPVPi_out->trip_counter > fcPVPi_out->time2trip * fs){

			fcPVPi_out->trip = 1;
			fcPVPi_out->trip_counter = 0;

		}



	}

	return fcPVPi_out->trip ;

}



















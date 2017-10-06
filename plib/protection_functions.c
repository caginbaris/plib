
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
// cs trip caution......


int fc27(struct fc27_inputParameters fc27_in, struct fc27_outputParameters *fc27_out,int enable ){

	if (enable){

		if (fc27_in.rms < fc27_in.level ){
		
			fc27_out->pick_up = 1;
		
		}


		if (fc27_in.rms > fc27_in.level*fc27_in.dropout_ratio ){
		
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














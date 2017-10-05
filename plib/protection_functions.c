
#include "protection_functions.h"

//function-1,2,3
//count  has to be initialized and supplied as different in each invocation



int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count){

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
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count){

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
int on_off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count){

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

int fc50(struct fc50_inputParameters fc50_in, struct fc50_outputParameters *fc50_out ){


	if(fc50_in.rms>fc50_in.level){ fc50_out->initial_pick_up=1;}
	if(fc50_in.rms<fc50_in.level*fc50_in.dropout_ratio){ fc50_out->initial_pick_up=0;}
	
	fc50_out->pick_up=off_delay(	fc50_out->initial_pick_up,
								   	fc50_out->pick_up,
									fc50_in.dropout_time,
									&(fc50_out->dropout_counter));

	fc50_out->trip=		on_delay(	fc50_out->pick_up,
								   	fc50_out->trip,
									fc50_in.delay,
									&(fc50_out->trip_counter));

	if(fc50_out->trip==1){fc50_out->trip_latch=1;}

	return fc50_out->trip_latch;

}





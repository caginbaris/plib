#define fs 2500

int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, unsigned int *count);
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, unsigned int *count);
int on_off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, unsigned int *count);

//------Definite Time Overcurrent-Start--------------------------------------------------------------------
struct fc50_inputParameters {

	float rms;
	float level;
	float dropout_ratio;

	unsigned int delay;
	unsigned int dropout_time;

};
struct fc50_outputParameters {

	unsigned int initial_pick_up:1;
	unsigned int pick_up:1;
	unsigned int trip:1;
	unsigned int trip_latch:1;

	unsigned int dropout_counter;
	unsigned int trip_counter;

};

int fc50(struct fc50_inputParameters fc50_in, struct fc50_outputParameters *fc50_out, int enable);
//------Definite Time Overcurrent-End---------------------------------------------------------------------


//------Inverse Time Overcurrent-Start--------------------------------------------------------------------
struct fc51_inputParameters {

	float rms;
	float level;
	float dropout_ratio;
	float curve_data[3];
	float time_multiplier;



};
struct fc51_outputParameters {

	float time2trip;
	long sample2trip;
	long trip_counter;
	
	unsigned int pick_up:1;
	unsigned int trip:1;



};

int fc51(struct fc51_inputParameters fc51_in, struct fc51_outputParameters *fc51_out,int enable );

//------Inverse Time Overcurrent-End--------------------------------------------------------------------


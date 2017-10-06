#define fs 2500

int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *count);
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *count);
int on_off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *count);

//------Definite Time Overcurrent-Start--------------------------------------------------------------------
struct fc50_inputParameters {

	float rms;
	float level;
	float dropout_ratio;
	float delay;
	float dropout_time;

};
struct fc50_outputParameters {

	long trip_counter;
	long dropout_counter;

	unsigned int initial_pick_up:1;
	unsigned int pick_up:1;
	unsigned int trip:1;
	unsigned int trip_latch:1;
	
	

};

int fc50(struct fc50_inputParameters fc50_in, struct fc50_outputParameters *fc50_out, int enable);
//------Definite Time Overcurrent-End---------------------------------------------------------------------


//------Inverse Time Overcurrent-Start--------------------------------------------------------------------
struct fc51_inputParameters {

	float rms;
	float level;
	float curve_data[3];
	float time_multiplier;


};
struct fc51_outputParameters {

	float time2trip;
	long trip_counter;
	
	unsigned int pick_up:1;
	unsigned int trip:1;



};

int fc51(struct fc51_inputParameters fc51_in, struct fc51_outputParameters *fc51_out,int enable );

//------Inverse Time Overcurrent-End--------------------------------------------------------------------

//------UnderVoltageProtection-Start--------------------------------------------------------------------

struct fc27_inputParameters{

	float rms;
	float level;
	float dropout_ratio;
	float delay;
	float dropout_time;
	unsigned int cs;

};


struct fc27_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};

int fc27(struct fc27_inputParameters fc27_in, struct fc27_outputParameters *fc27_out,int enable );

//------UnderVoltageProtection-End--------------------------------------------------------------------


//------OverVoltageProtection-Start--------------------------------------------------------------------

struct fc59_inputParameters{

	float rms;
	float level;
	float dropout_ratio;
	float delay;
	float dropout_time;
	unsigned int cs;

};


struct fc59_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};

int fc59(struct fc59_inputParameters fc59_in, struct fc59_outputParameters *fc59_out,int enable );


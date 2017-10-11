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

void fc50(struct fc50_inputParameters fc50_in, struct fc50_outputParameters *fc50_out, int enable);
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

void fc51(struct fc51_inputParameters fc51_in, struct fc51_outputParameters *fc51_out,int enable );

//------Inverse Time Overcurrent-End--------------------------------------------------------------------

//------UnderVoltageProtection-Start--------------------------------------------------------------------

struct fc27_inputParameters{

	float rms;
	float level;
	float dropout_ratio;
	float delay;
	unsigned int cs; // caution: externally set by a routine

};


struct fc27_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};

void fc27(struct fc27_inputParameters fc27_in, struct fc27_outputParameters *fc27_out,int enable );

//------UnderVoltageProtection-End--------------------------------------------------------------------


//------OverVoltageProtection-Start--------------------------------------------------------------------

struct fc59_inputParameters{

	float rms;
	float level;
	float dropout_ratio;
	float delay;
	unsigned int cs;

};


struct fc59_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};

void fc59(struct fc59_inputParameters fc59_in, struct fc59_outputParameters *fc59_out,int enable );

//------OverVoltageProtection-End--------------------------------------------------------------------


//------NegativeSequenceProtection-Start------------------------------------------------------------

struct fc46d_inputParameters{

	float rms;
	float level;
	float delay;
	float dropout_time;
	float dropout_ratio;

};


struct fc46d_outputParameters{

	
	long trip_counter;
	long dropout_counter;

	unsigned int initial_pick_up:1;
	unsigned int pick_up:1;
	unsigned int trip:1;
	unsigned int trip_latch:1;

};



struct fc46i_inputParameters {

	float rms;
	float level;
	float curve_data[3];
	float time_multiplier;

};
struct fc46i_outputParameters {

	float time2trip;
	long trip_counter;
	
	unsigned int pick_up:1;
	unsigned int trip:1;


};

void fc46d(struct fc46d_inputParameters fc46d_in, struct fc46d_outputParameters *fc46d_out, int enable);
void fc46i(struct fc46i_inputParameters fc46i_in, struct fc46i_outputParameters *fc46i_out, int enable);

//------NegativeSequenceProtection-End---------------------------------------------------



//------ThermalProtection-Start------------------------------------------------------------

struct fc49_inputParameters{

	float temp;
	float alarm_level; 
	float trip_level; 
	float dropout_ratio;

};


struct fc49_outputParameters{

	
	unsigned int alarm:1;
	unsigned int trip:1;
	

};

void fc49(struct fc49_inputParameters fc49_in, struct fc49_outputParameters *fc49_out, int enable);

//------ThermalProtection-End------------------------------------------------------------

//------Breaker Failure-Start------------------------------------------------------------

struct fcBF_inputParameters{

	float rmsA;
	float rmsB;
	float rmsC;

	float threshold;
	float delay;

	

	unsigned int trip_input:1;
	unsigned int CB_pos:1;
	unsigned int CB_pos_check:1;


	

};

struct fcBF_outputParameters{

	
	long trip_counter;
	long pass_flag_counter;

	unsigned int pick_up:1;
	unsigned int current_checked:1;
	unsigned int trip:1;
	unsigned int pass_flag:1;
	unsigned int pass_flag_filtered:1;
	
	



};


void fcBF(struct fcBF_inputParameters fcBF_in, struct fcBF_outputParameters *fcBF_out, int enable);



//------Breaker Failure-End--------------------------------------------------------------


//------UnderCurrent-Start------------------------------------------------------------
struct fc37_inputParameters{

	float rms;
	float level;
	float dropout_ratio;
	float delay;
	unsigned int bs; // will be assigned to CB position

};


struct fc37_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};

void fc37(struct fc37_inputParameters fc37_in, struct fc37_outputParameters *fc37_out, int enable);

//------UnderCurrent-End--------------------------------------------------------------

//------Unbalace-Start------------------------------------------------------------

struct fcUNBd_inputParameters{

	float rms;
	float level; // vectoral difference will be used
	float dropout_ratio;
	float delay;
	

};

struct fcUNBd_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};



struct fcUNBi_inputParameters {

	float rms;
	float level;
	float curve_data[3];
	float time_multiplier;

	
};


struct fcUNBi_outputParameters{

	float time2trip;
	long trip_counter;
	
	unsigned int pick_up:1;
	unsigned int trip:1;
};


void fcUNBd(struct fcUNBd_inputParameters fcUNBd_in, struct fcUNBd_outputParameters *fcUNBd_out, int enable);
void fcUNBi(struct fcUNBi_inputParameters fcUNBi_in, struct fcUNBi_outputParameters *fcUNBi_out, int enable);

//------Unbalace-Start------------------------------------------------------------

struct fcPVPd_inputParameters{

	float rms;
	float level; // vectoral difference will be used
	float dropout_ratio;
	float delay;
	

};

struct fcPVPd_outputParameters{

	long trip_counter;
	unsigned int pick_up:1;
	unsigned int trip:1;

};


struct fcPVPi_inputParameters {

	float rms;
	float level;
	float curve_data[3];
	float time_multiplier;


};


struct fcPVPi_outputParameters{

	float time2trip;
	long trip_counter;
	
	unsigned int pick_up:1;
	unsigned int trip:1;
};

void fcPVPd(struct fcPVPd_inputParameters fcPVPd_in, struct fcPVPd_outputParameters *fcPVPd_out, int enable);
void fcPVPi(struct fcPVPi_inputParameters fcPVPi_in, struct fcPVPi_outputParameters *fcPVPi_out, int enable);



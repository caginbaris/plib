


int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count);
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count);
int on_off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count);


struct fc50_inputParameters{

float rms;
float level;
float delay;
float dropout_ratio;
float dropout_time;

};
struct fc50_outputParameters{

unsigned int initial_pick_up:1;
unsigned int pick_up:1;
unsigned int trip:1;
unsigned int trip_latch:1;


unsigned int dropout_counter;
unsigned int trip_counter;


};

int fc50(struct fc50_inputParameters fc50_in, struct fc50_outputParameters *fc50_out );

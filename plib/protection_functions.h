


int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count);
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count);
int on_off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample,unsigned int *count);


struct fc50_inputParameters{

float level;
float delay;
float drop_out_ratio;
float drop_out_time;

int rms_selection;

};
struct fc50_outputParameters{
int pick_up:1;
int trip:1;


};

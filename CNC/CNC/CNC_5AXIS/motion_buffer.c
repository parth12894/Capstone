#include "CNC_5Axis.h"

// Variables to keep track of the ring buffer
static volatile uint32_t motion_buffer_head;
static volatile uint32_t motion_buffer_tail;

/*Adds a linear motion block to the head of the motion buffer*/
void update_motion_buffer(float* target_pos, float* curr_pos, float feedrate)
{
    uint8_t i;
    uint32_t target_steps[N_AXIS];
	float target_joints[N_AXIS];
	
	for(i=0;i<N_AXIS;i++)
		target_joints[i] = target_pos[i] - curr_pos[i];
	
	
	uint32_t next_buffer_head = (motion_buffer_head + 1) % MOTION_BUFFER_SIZE;

	// If the buffer is full; rest here until there is room in the buffer.
	while(motion_buffer_tail == next_buffer_head){};
	
    motion_block_t *block = &motion_buffer[motion_buffer_head];
	block->is_Mcode = 0;
    block->max_step_count = 0;
	
	// Convert feedrate to clock cycles.
	block->feedrate = (int) (FEED_RATE_PARAMETER / feedrate);
	
	// Calculate steps for each axis.
	block->steps[X_AXIS] = lround(target_joints[X_AXIS]*STEPS_PER_MM_X);
	block->steps[Y_AXIS] = lround(target_joints[Y_AXIS]*STEPS_PER_MM_Y);
	block->steps[Z_AXIS] = lround(target_joints[Z_AXIS]*STEPS_PER_MM_Z);
	block->steps[A_AXIS] = lround(target_joints[A_AXIS]*STEPS_PER_DEGREE); 	
	block->steps[C_AXIS] = lround(target_joints[C_AXIS]*STEPS_PER_DEGREE);	
	
	// Calculate direction for each axis.
	for(i=0;i<N_AXIS;i++)
	{
		if((int)(block->steps[i]) < 0)
			block->dir[i] = 0;
		else
			block->dir[i] = 1;
		block->steps[i] = abs(block->steps[i]);		
		block->max_step_count = max(block->max_step_count,block->steps[i]);
	}    
	
	#if DEBUG
		block->millimeters = 0;
		block->radians = 0;
		
		block->millimeters += square(abs(target_joints[X_AXIS]));
		block->millimeters += square(abs(target_joints[Y_AXIS]));
		block->millimeters += square(abs(target_joints[Z_AXIS]));
		block->radians += square(abs(target_joints[A_AXIS]));
		block->radians += square(abs(target_joints[C_AXIS]));
		
		block->millimeters = sqrt(block->millimeters);
		block->radians = sqrt(block->radians);
		
		printf("Steps: %d %d %d %d %d \nFeedrate: %f\nBufferHead: %d\nMillimeters: %.4f\nRadians: %.4f\n\n",block->steps[X_AXIS],block->steps[Y_AXIS],block->steps[Z_AXIS],block->steps[A_AXIS],block->steps[C_AXIS],feedrate,motion_buffer_head,block->millimeters,block->radians);
	#endif
	
	motion_buffer_head = next_buffer_head;
	
	#if RUN_MOTORS
		ISR_EN();
	#endif
	return;
}


void add_M_block(uint8_t code, uint32_t speed, uint32_t parameter)
{
	int next_buffer_head = (motion_buffer_head + 1) % MOTION_BUFFER_SIZE;

	// If the buffer is full; rest here until there is room in the buffer.
	while(motion_buffer_tail == next_buffer_head){};
	
	motion_block_t *block = &motion_buffer[motion_buffer_head];
	
	//add m parameters to the motion block
	block->is_Mcode = 1;
	block->code = code;
	block->speed = speed;
	block->parameter = parameter;
	
	motion_buffer_head = next_buffer_head;
	
	#if DEBUG
		printf("M Code: %d\nSpeed: %f\nBufferHead: %d\Parameter: %d\n\n",code,speed,motion_buffer_head,parameter);
	#endif
	#if RUN_MOTORS
		ISR_EN();
	#endif
	
	return;
}

motion_block_t *get_motion_block(){
    if (motion_buffer_head == motion_buffer_tail) { return(NULL); }
    return(&motion_buffer[motion_buffer_tail]);
}

inline void increment_current_block() {
	if (motion_buffer_head != motion_buffer_tail)
		motion_buffer_tail = (motion_buffer_tail + 1) % MOTION_BUFFER_SIZE;
}

 int get_head() {
	 return motion_buffer_head;
 }

 int get_tail() {
	 return motion_buffer_tail;
 }
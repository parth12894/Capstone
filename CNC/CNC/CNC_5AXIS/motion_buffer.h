#ifndef MOTION_BUFFER_H_
#define MOTION_BUFFER_H_

// Used for stepper control
typedef struct{

	uint32_t steps[N_AXIS];
	uint32_t max_step_count;
	uint8_t dir[N_AXIS];
	float feedrate;
	
	uint8_t is_Mcode;
	uint8_t code;
	uint32_t speed;
	uint32_t parameter;
	
	#if DEBUG_ISR
		uint32_t bufferhead;
		float millimeters;
		float radians;
	#endif
}motion_block_t;

static motion_block_t motion_buffer[MOTION_BUFFER_SIZE];

void update_motion_buffer(float* target, float*offset, float feedrate);

motion_block_t *get_motion_block();

void increment_current_block();	

void add_M_block(uint8_t code, uint32_t speed, uint32_t parameter);

int get_head();

int get_tail();

#endif
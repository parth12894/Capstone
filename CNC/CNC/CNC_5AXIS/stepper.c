#include "CNC_5Axis.h"


volatile uint8_t x_enable,
				 y_enable,
				 z_enable,
				 a_enable,
				 c_enable;

volatile uint32_t counter_x, 
				  counter_y,
				  counter_z,
				  counter_a,
				  counter_c,
				  step_events_completed;

static motion_block_t *current_block = NULL;

struct timer_task stepper_ISR_task, stepper_low_ISR_task, task2;


void stepper_ISR(const struct timer_task *const timer_task)
{
	gpio_set_pin_level(DGI_GPIO0, true);
	delay_us(10);
	
	if (current_block == NULL)
	{	
		// If current block is NULL; Fetch a new block.
		current_block = get_motion_block();
		if (current_block == NULL)
		{
			ISR_disable();
			return;
		}
		
		#if DEBUG_ISR
			printf("\n---Executing block #%d---\n", current_block->bufferhead);
		#endif
		
		// If current block is a M block, execute it and the return.
		if(current_block->is_Mcode == 1)
		{
			run_M_code(current_block->code,current_block->speed,current_block->parameter);
			return;
		}
		
		
		// Initialize Bresenham line and distance counters.	
		step_events_completed = 0;
		counter_x = counter_y = counter_z = counter_a = counter_c = (current_block->max_step_count >> 1);
		
		// Setup the feedrate for this block.
		timer_set_clock_cycles_per_tick(&TIMER_1,current_block->feedrate);
		
		// Setup the directions for this block.
		if(current_block->dir[X_AXIS] == 1)
			gpio_set_pin_level(X_DIR, true);
		else
			gpio_set_pin_level(X_DIR, false);

		if(current_block->dir[Y_AXIS] == 1)
			gpio_set_pin_level(Y_DIR, true);
		else
			gpio_set_pin_level(Y_DIR, false);

		if(current_block->dir[Z_AXIS] == 1)
			gpio_set_pin_level(Z_DIR, true);
		else
			gpio_set_pin_level(Z_DIR, false);

		if(current_block->dir[A_AXIS] == 1)
			gpio_set_pin_level(A_DIR, true);
		else
			gpio_set_pin_level(A_DIR, false);

		if(current_block->dir[C_AXIS] == 0)
			gpio_set_pin_level(C_DIR, true);
		else
			gpio_set_pin_level(C_DIR, false);

	}

	
	// Integer based Bresenham algorithm.
	counter_x += current_block->steps[X_AXIS];
	if (counter_x > current_block->max_step_count)
	{
		x_enable = 1;
		counter_x -= current_block->max_step_count;
	}
	counter_y += current_block->steps[Y_AXIS];
	if (counter_y > current_block->max_step_count)
	{
		y_enable = 1;
		counter_y -= current_block->max_step_count;
	}
	counter_z += current_block->steps[Z_AXIS];
	if (counter_z > current_block->max_step_count)
	{
		z_enable = 1;
		counter_z -= current_block->max_step_count;
	}
	counter_a += current_block->steps[A_AXIS];
	if (counter_a > current_block->max_step_count)
	{
		a_enable = 1;
		counter_a -= current_block->max_step_count;
	}
	counter_c += current_block->steps[C_AXIS];
	if (counter_c > current_block->max_step_count)
	{
		c_enable = 1;
		counter_c -= current_block->max_step_count;
	}
	
	step_events_completed++;

	// Turn on the necessary step pins.
	if (x_enable == 1)
		gpio_set_pin_level(X_STEP, true);
	if (y_enable == 1)
		gpio_set_pin_level(Y_STEP, true);
	if (z_enable == 1)
		gpio_set_pin_level(Z_STEP, true);
	if (a_enable == 1)
		gpio_set_pin_level(A_STEP, true);
	if (c_enable == 1)
		gpio_set_pin_level(C_STEP, true);

	// Turn off the step pins independently.
	timer_add_task(&TIMER_0, &stepper_low_ISR_task);

	// When current block is done, increment it. 
	if (step_events_completed >= current_block->max_step_count)
	{
		#if DEBUG_ISR
			printf("\n---Done block #%d---\n", current_block->bufferhead);
		#endif
		current_block = NULL;
		increment_current_block();
	}
	
	gpio_set_pin_level(DGI_GPIO0, false);
	return;
}

void stepper_low_ISR(const struct timer_task *const timer_task)
{
	gpio_set_pin_level(X_STEP, false);
	gpio_set_pin_level(Y_STEP, false);
	gpio_set_pin_level(Z_STEP, false);
	gpio_set_pin_level(A_STEP, false);
	gpio_set_pin_level(C_STEP, false);
	x_enable = 0;
	y_enable = 0;
	z_enable = 0;
	a_enable = 0;
	c_enable = 0;
	
	return;
}

void stepper_init()
{
	// Initialize the timer tasks
	stepper_ISR_task.interval = 1;
	stepper_ISR_task.cb = stepper_ISR;
	stepper_ISR_task.mode = TIMER_TASK_REPEAT;

	stepper_low_ISR_task.interval = 1; 
	stepper_low_ISR_task.cb = stepper_low_ISR;
	stepper_low_ISR_task.mode = TIMER_TASK_ONE_SHOT;
	
	
	timer_add_task(&TIMER_1, &stepper_ISR_task);
	timer_start(&TIMER_0);
	return;
}

void ISR_disable()
{
	current_block = NULL;
	increment_current_block();
	#define ISR_DIS() timer_stop(&TIMER_1);
}


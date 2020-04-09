#include "CNC_5Axis.h"


void add_linear_motion(float *target_pos, float *curr_pos, float feedrate)
{
	#if DEBUG
		printf("Current Position: %f %f %f %f %f\n",curr_pos[X_AXIS],curr_pos[Y_AXIS],curr_pos[Z_AXIS],curr_pos[A_AXIS],curr_pos[C_AXIS]);
		printf("Next Position: %f %f %f %f %f\n",target_pos[X_AXIS],target_pos[Y_AXIS],target_pos[Z_AXIS],target_pos[A_AXIS],target_pos[C_AXIS]);
	#endif
	
	update_motion_buffer(target_pos,curr_pos,feedrate);
}

void add_arc_motion(float *position, float *target, float *offset, uint8_t axis_0, uint8_t axis_1, uint8_t axis_linear, uint8_t is_CW, float feedrate)
{
	// Details: target and offset is wrt position to origin

	/* set up vectors */
	float center_axis0 = position[axis_0] + offset[axis_0];
	float center_axis1 = position[axis_1] + offset[axis_1];
	/* radius vector from center to current position */
	float r_axis0 = -offset[axis_0];
	float r_axis1 = -offset[axis_1];
	/* radius vector from center to target position */
	float rt_axis0 = target[axis_0] - offset[axis_0];
	float rt_axis1 = target[axis_1] - offset[axis_1];
	
	// used for final buffer update
	uint16_t i;
	float absolute_target[N_AXIS];
	for(i=0;i<N_AXIS;i++)
		absolute_target[i] = position[i] + target[i];
	
	
	/* find angular travel and direction */	
	/* We use atan2 for full angular range support. r_axis is considered to be the positive x-axis.
	We need to interpret ang_travel to fit this fact.*/
	float ang_travel = atan2(r_axis0*rt_axis1 - r_axis1*rt_axis0,r_axis0*rt_axis0 + r_axis1*rt_axis1);
	switch(is_CW)
	{
		case 1: 
			if(sign(ang_travel)==1)
				ang_travel = -(2*PI - ang_travel);
			break;
		case 0:
			if(sign(ang_travel)==-1)
				ang_travel = 2*PI + ang_travel;
	}
	
	#if DEBUG
		printf("ang_travel %f\n", ang_travel);
	#endif

	/* get segments based on pre-defined total secant error */
    uint16_t segments = ceil((square(ang_travel))/(32*TOTAL_SECANT_ERROR));
	if (segments < MINIMUM_SEGMENTS)
		segments = MINIMUM_SEGMENTS;
	
	#if DEBUG
		printf("Number of segments: %d\n",segments);
	#endif
	
	float theta_per_segment = ang_travel/segments;
	float linear_per_segment = target[axis_linear]/segments;
	// variables for incremental cos and sin
	float cos_T = 2.0-theta_per_segment*theta_per_segment;
	float sin_T = theta_per_segment*(cos_T + 4.0)/6.0;
	cos_T = cos_T/2;
	
	/* variables for arc correction */
	float sin_Ti;
	float cos_Ti;
	float r_axis_temp;
	float current_position[N_AXIS];
	uint8_t count=0;
	
	for(i=1;i<segments;i++){
	
		if (count<ERROR_CORRECTION_COUNT){
			r_axis_temp = r_axis0*sin_T + r_axis1*cos_T;
			r_axis0 = r_axis0*cos_T - r_axis1*sin_T;
			r_axis1 = r_axis_temp;
			count++;
		}else{
			cos_Ti = cos(i*theta_per_segment);
			sin_Ti = sin(i*theta_per_segment);
			r_axis0 = -offset[axis_0]*cos_Ti + offset[axis_1]*sin_Ti;
			r_axis1 = -offset[axis_0]*sin_Ti - offset[axis_1]*cos_Ti;
			count=0;	   	   	   
		}
		
		memcpy(current_position,position,N_AXIS*sizeof(float));
		
		/* update arc location */
		position[axis_0] = center_axis0 + r_axis0;
		position[axis_1] = center_axis1 + r_axis1;
		/* for helical motion */
		position[axis_linear] += linear_per_segment;
		
		#if DEBUG
			printf("Current Position: %f %f %f %f %f\n",current_position[X_AXIS],current_position[Y_AXIS],current_position[Z_AXIS],current_position[A_AXIS],current_position[C_AXIS]);
			printf("Next Position: %f %f %f %f %f\n",position[X_AXIS],position[Y_AXIS],position[Z_AXIS],position[A_AXIS],position[C_AXIS]);
		#endif

		update_motion_buffer(position,current_position,feedrate);
		memcpy(current_position,position,N_AXIS*sizeof(float));
	}
	
	/*make sure final position is at target*/
	memcpy(position,absolute_target,N_AXIS*sizeof(float));
	#if DEBUG
		printf("Current Position: %f %f %f %f %f\n",current_position[X_AXIS],current_position[Y_AXIS],current_position[Z_AXIS],current_position[A_AXIS],current_position[C_AXIS]);
		printf("Next Position: %f %f %f %f %f\n",position[X_AXIS],position[Y_AXIS],position[Z_AXIS],position[A_AXIS],position[C_AXIS]);
	#endif
	update_motion_buffer(absolute_target,current_position,feedrate);
}


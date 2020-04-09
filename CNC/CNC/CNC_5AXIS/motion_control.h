#ifndef MOTION_CONTROL_H_
#define MOTION_CONTROL_H_

void add_linear_motion(float *target_pos, float* curr_pos, float feedrate);

void add_arc_motion(float *position, float *target, float *offset, uint8_t axis_0, uint8_t axis_1, uint8_t axis_linear, uint8_t is_CW, float feedrate);

#endif
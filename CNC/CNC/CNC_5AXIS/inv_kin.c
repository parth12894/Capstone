#include "CNC_5Axis.h"

void* inv_kin_slow(float *out, float *pose, float *offset)
{
	uint8_t i;
	for(i=0;i<N_AXIS;i++)
		out[i] = pose[i] - offset[i];
		
	return 0;
}
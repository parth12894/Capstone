#ifndef inv_kin_h
#define inv_kin_h

/* enter pose in millimeters and radians, outputs joint parameters
in millimeters and radians*/
void* inv_kin_slow(float *out, float *pose, float *offset);


#endif
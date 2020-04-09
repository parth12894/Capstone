#include "CNC_5Axis.h"

float **for_kin_slow_AC(float A, float C){
	float **rotmat;
	// allocate memory for the 2d array
	int i;
	rotmat = malloc(sizeof(float*)*3);
	for(i=0;i<3;i++){
		rotmat[i] = malloc(sizeof(float*)*3);
	}

	rotmat[0][0]=cos(C);
	rotmat[0][1]=-cos(A)*sin(C);
	rotmat[0][2]=sin(A)*sin(C);
	rotmat[1][0]=sin(C);
	rotmat[1][1]=cos(A)*cos(C);
	rotmat[1][2]=-cos(C)*sin(A);
	rotmat[2][0]=0;
	rotmat[2][1]=sin(A);
	rotmat[2][2]=cos(A);

	return rotmat;

}
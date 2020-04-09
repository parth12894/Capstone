#ifndef CNC_5AXIS_H_
#define	CNC_5AXIS_H_


// Debugging
#define DEBUG 0
#define DEBUG_ISR 0
#define RUN_MOTORS 1


// Globals Parameters
#define INCHES_PER_MM 25.4
#define MOTION_BUFFER_SIZE 4096
#define PI 3.14158265358979323846
#define TOTAL_SECANT_ERROR 0.003
#define ERROR_CORRECTION_COUNT 5
#define MINIMUM_SEGMENTS 32


// Machine Dependent Parameters
#define STEPS_PER_MM_X 1280.0
#define STEPS_PER_MM_Y 1280.0
#define STEPS_PER_MM_Z 1600.0
#define MAX_FEEDRATE 1150
#define STEPS_PER_DEGREE 71.111111111 //4074.3665

//	Convert feedrate from mm/min to cycles/step 
// ((60x18.8x10^6) / (Fx1280)) = 881250/F
#define FEED_RATE_PARAMETER 881250				
// This will generate a 1KHz PWM if using PCLK/64
#define PWM_PERIOD 2340							


// Useful names
#define HIGH true
#define LOW false

#define N_AXIS 5
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define A_AXIS 3
#define C_AXIS 4


// Fast math
#ifndef sign
    #define sign(x) ((x>=0)-(x<0))
#endif

#ifndef square
	#define square(x) (x*x)
#endif


// C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

//Project Libraries
#include "pin_define.h"
#include "parser.h"
#include "motion_control.h"
#include "motion_buffer.h"
#include "stepper.h"
#include "spindle.h"
#include "filesystem.h"
#include "limits.h"

//Atmel Libraries
#include <atmel_start.h>
#include <diskio.h>
#include <ff.h>
#include <sd_mmc.h>
#include <sd_mmc_protocol.h>


#endif


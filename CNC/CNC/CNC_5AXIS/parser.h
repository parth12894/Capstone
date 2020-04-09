#ifndef PARSER_H_
#define PARSER_H_

#define GCODE 0
#define MCODE 1

#define ABS_MODE 0
#define INC_MODE 1


// used to keep track of G-code inputs
typedef struct{

    float feedrate; //feedrate in units/min
    float ijk[3]; // for offsets
    float xyzac[5]; // for target position
	
	uint32_t p,s;
	
	uint8_t code;
}parser_input_t;

extern parser_input_t parser_input;

// used to keep track of state of machine
typedef struct{

    float feedrate; // current feedrate of the tool
    float position[5]; //current position of the tool 
    uint8_t plane[2]; // plane of curve motions. Default:XY
    uint8_t axis_linear; // linear axis for Helical motion
	
	float multiplier;
	uint8_t abs_or_inc;
	uint32_t spindle_speed;
}parser_state_t;

extern parser_state_t parser_state;

void parser_init();

void parse_line(char *line);

void set_cord_to_zero(uint axis);

float get_float_after_letter(char * str,uint8_t *char_counter);

#endif


/*
 Supported GCodes / MCodes / Parameters

G0 = Fast Linear Move
G1 = Linear Move
G2 = Arc clockwise
G3 = Arc counter-clockwise
G4 = Dwell For P seconds
G17 = Select plane XY
G18 = Select plane XZ
G19 = Select plane YZ
G20 = Programing in Inches
G21 = Programing in Millimeters
G28 = Go to Machine zero
G90 = Programing in Absolute mode
G91 = Programing in Incremental mode
G92 = Set current position as machine ZERO
G93 = Units per minute feed rate mode

M3 = Spindle ON
M4 = Spindle ON
M5 = Spindle OFF
M7 = Mist Coolant ON
M8 = Flood Coolant ON
M9 = Coolant OFF

X = X axis (in mm/inch)
Y = Y axis (in mm/inch)
Z = Z axis (in mm/inch)
A = A axis (in degrees/rad)
C = C axis (in degrees/rad)
I = X offset
J = Y offset
K = Z offset
F = Feed-rate unit/min
S = Spindle Speed (0-100)
P = Parameter; Used for Dwell indicates seconds

; = Comment Line
* = Display current debug status
$# = Run File '#.txt', '#' needs to be an integer
*/
#include "CNC_5Axis.h"

parser_input_t parser_input;
parser_state_t parser_state;

void parser_init()
{
	// Initialize the parser with default parameters. 
    memset(&parser_state,0,sizeof(parser_state_t));
	memset(&parser_input,0,sizeof(parser_input_t));
	
    parser_state.plane[0] = X_AXIS;
    parser_state.plane[1] = Y_AXIS; // Default XY Plane
    parser_state.axis_linear = Z_AXIS; 
	
	parser_state.multiplier = 1;
	parser_state.abs_or_inc = ABS_MODE;
	parser_state.feedrate = 500;

}


void parse_line(char *line)
{
    uint8_t command = 255;
	uint8_t is_G_or_M_code = 255;
    uint8_t char_counter;
    char letter;
	
	char_counter = 1;
	command = (int)get_float_after_letter(line,&char_counter);
	char_counter = 0;
	
	if(line[0] == ';')
		return;	
	else if(line[0] =='G')
		is_G_or_M_code = GCODE;
	else if(line[0] =='M')
		is_G_or_M_code = MCODE;
	else if(line[0] =='$')
	{
		execute_from_sd_card(command);
		return;
	}
	else if(line[0] =='*')
	{
		printf("State:\nPosition: X%f Y%f Z%f A%f C%f\nPlane: %d %d\nVertical: %d",parser_state.position[0],parser_state.position[1],parser_state.position[2],parser_state.position[3],parser_state.position[4],parser_state.plane[0],parser_state.plane[1],parser_state.axis_linear);
		printf("\n Feedrate: %.2f", parser_state.feedrate);
		
		if(parser_state.multiplier == 1)
			printf("\n Millimeter Mode");
		else
			printf("\n Inches Mode");
			
		if(parser_state.abs_or_inc == ABS_MODE)
			printf("\n Absolute Mode");
		else
			printf("\n Incremental Mode \n");
		return;
	}	
	else
	{	
		printf("ERROR: Not a G or M Command\n%s \n",line); 
		return;
	}
	
	
	// Once command is set, get parameter values
    while(line[char_counter] != 0)				
	{ 
        char_counter++;
        letter = line[char_counter];

        switch(letter)
		{
            case 'X':
                char_counter++;
                parser_input.xyzac[X_AXIS] = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				if(parser_state.abs_or_inc == INC_MODE) parser_input.xyzac[X_AXIS] = parser_state.position[X_AXIS] + parser_input.xyzac[X_AXIS];

				break;
            case 'Y':
                char_counter++;
                parser_input.xyzac[Y_AXIS] = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				if(parser_state.abs_or_inc == INC_MODE) parser_input.xyzac[Y_AXIS] = parser_state.position[Y_AXIS] + parser_input.xyzac[Y_AXIS];
				break;
            case 'Z':
                char_counter++;
                parser_input.xyzac[Z_AXIS] = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				if(parser_state.abs_or_inc == INC_MODE) parser_input.xyzac[Z_AXIS] = parser_state.position[Z_AXIS] + parser_input.xyzac[Z_AXIS];
				break;
            case 'A':
                char_counter++;
                parser_input.xyzac[A_AXIS] = get_float_after_letter(line,&char_counter);
				if(parser_state.abs_or_inc == INC_MODE) parser_input.xyzac[A_AXIS] = parser_state.position[A_AXIS] + parser_input.xyzac[A_AXIS];
				break;
            case 'C':
                char_counter++;
                parser_input.xyzac[C_AXIS] = get_float_after_letter(line,&char_counter);
				if(parser_state.abs_or_inc == INC_MODE) parser_input.xyzac[C_AXIS] = parser_state.position[C_AXIS] + parser_input.xyzac[C_AXIS];
				break;
            case 'I':
                char_counter++;
                parser_input.ijk[X_AXIS] = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				break;
            case 'J':
                char_counter++;
                parser_input.ijk[Y_AXIS] = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				break;
            case 'K':
                char_counter++;
                parser_input.ijk[Z_AXIS] = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				break;
            case 'F':
                char_counter++;
                parser_input.feedrate = parser_state.multiplier * get_float_after_letter(line,&char_counter);
				
				if(parser_input.feedrate < MAX_FEEDRATE)
					parser_state.feedrate = parser_input.feedrate;
				else
					parser_state.feedrate = MAX_FEEDRATE;
				break;
			case 'P':
				char_counter++;
				parser_input.p = get_float_after_letter(line,&char_counter);
				break;
			case 'S':
				char_counter++;
				parser_input.s = get_float_after_letter(line,&char_counter);
				break;
        }
    } 
    
	

    // Execute the line
    float input_relative[N_AXIS],num2;
    int i, num1;
	
    if (is_G_or_M_code == GCODE)
	{
		switch(command)
		{
			case 0:
				#if DEBUG
					printf("RAPID LINEAR MOVE\n");
				#endif
				add_linear_motion(parser_input.xyzac, parser_state.position,800);
				memcpy(parser_state.position,parser_input.xyzac,N_AXIS*sizeof(float));
				break;
			case 1:
				#if DEBUG
					printf("LINEAR MOVE\n");
				#endif
				add_linear_motion(parser_input.xyzac, parser_state.position,parser_state.feedrate);
				memcpy(parser_state.position,parser_input.xyzac,N_AXIS*sizeof(float));
				break;
			case 2:
				/* The target input is relative to the position. So we need to convert the absolute G command arguments
					to relative.*/
				for (i=0;i<N_AXIS;i++)
					input_relative[i] = parser_input.xyzac[i] - parser_state.position[i];
	
				#if DEBUG
					printf("CURVE/HELICAL MOVE CW\n");
					printf("relative position: %f %f %f %f %f\n\n", input_relative[X_AXIS],input_relative[Y_AXIS],input_relative[Z_AXIS],
						input_relative[A_AXIS],input_relative[C_AXIS]);
				#endif
	
				add_arc_motion(parser_state.position,input_relative,parser_input.ijk,parser_state.plane[0],parser_state.plane[1],parser_state.axis_linear,1,parser_state.feedrate);
				break;
			case 3:
				for (i=0;i<N_AXIS;i++)
					input_relative[i] = parser_input.xyzac[i] - parser_state.position[i];
	
				#if DEBUG
					printf("CURVE/HELICAL MOVE CCW\n");
					printf("relative position: %f %f %f %f %f\n\n", input_relative[X_AXIS],input_relative[Y_AXIS],input_relative[Z_AXIS],
						input_relative[A_AXIS],input_relative[C_AXIS]);
				#endif
	
				add_arc_motion(parser_state.position,input_relative,parser_input.ijk,parser_state.plane[0],parser_state.plane[1],parser_state.axis_linear,0,parser_state.feedrate);
				break;
			case 4:
				#if DEBUG
					printf("DWELLING\n");
				#endif
					//add_M_block(100,parser_input.s,parser_input.p);
				break;
			case 17:
				#if DEBUG
					printf("Plane: XY\n");
				#endif
				parser_state.plane[0] = X_AXIS;
				parser_state.plane[1] = Y_AXIS;
				parser_state.axis_linear = Z_AXIS;
				break;
			case 18:
				#if DEBUG
					printf("Plane: XZ\n");
				#endif
				parser_state.plane[0] = X_AXIS;
				parser_state.plane[1] = Z_AXIS;
				parser_state.axis_linear = Y_AXIS;
				break;
			case 19:
				#if DEBUG
					printf("Plane: YZ\n");
				#endif
				parser_state.plane[0] = Y_AXIS;
				parser_state.plane[1] = Z_AXIS;
				parser_state.axis_linear = X_AXIS;
				break;
			case 20:
				#if DEBUG
					printf("Programing in Inches\n");
				#endif
				parser_state.multiplier = INCHES_PER_MM;
				break;
			case 21:
				#if DEBUG
					printf("Programing in Millimeters \n");
				#endif
				parser_state.multiplier = 1;
				break;
			case 28:
				#if DEBUG
					printf("Go To machine Zero\n");
				#endif
				num1 = parser_state.abs_or_inc;
				num2 = parser_state.feedrate;
				parser_state.abs_or_inc = ABS_MODE;
				parse_line("G1 X0 Y0 Z0 A0 C0 F500");
				parser_state.abs_or_inc = num1;
				parser_state.feedrate = num2;
				break;
			case 90:
				#if DEBUG
					printf("Programing in Absolute mode \n");
				#endif
				parser_state.abs_or_inc = ABS_MODE;
				break;
			case 91:
				#if DEBUG
					printf("Programing in Incremental mode \n");
				#endif
				parser_state.abs_or_inc = INC_MODE;
				break;	
				
			case 92:
				#if DEBUG
					printf("Setting current position as machine ZERO\n");
				#endif
				memset(&parser_input,0,sizeof(parser_input_t));
				memcpy(parser_state.position,parser_input.xyzac,N_AXIS*sizeof(float));
				break;
			default:
				printf("This G-code not supported!\n");
				return;
				break;	
		}
		
		return;
	} 
	else
	{
		switch(command)
		{
			case 3:
			case 4:
				#if DEBUG
					printf("Spindle ON Speed:%d\n", parser_input.s);
				#endif
				break;
			case 5:
				#if DEBUG
					printf("Spindle OFF\n");
				#endif
				break;
			case 7:
				#if DEBUG
					printf("Mist Coolant ON\n");
				#endif
				break;
			case 8:
				#if DEBUG
					printf("Flood Coolant ON\n");
				#endif
				break;
			case 9:
				#if DEBUG
					printf("Coolant OFF\n");
				#endif
				break;
			default:
				printf("This code not supported!\n");
				return;
				break;
		}
		
		add_M_block(command,parser_input.s,parser_input.p);
		
		return;
	}
}

void set_cord_to_zero(uint axis)
{
	parser_state.position[axis] = 0.0;
	return;
}

float get_float_after_letter(char * str,uint8_t *char_counter)
{
	char float_str[9] = {0};
	uint8_t float_ctr = 0;
	
	while(str[*char_counter]!=' '&&str[*char_counter]!=0){
		float_str[float_ctr] = str[*char_counter];
		float_ctr++;
		*char_counter = *char_counter + 1;
	}
	
	return atof(float_str);
}

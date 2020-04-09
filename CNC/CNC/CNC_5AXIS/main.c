#include "CNC_5AXIS/CNC_5Axis.h"


int main()
{
	// Initialize all the individual components
	atmel_start_init();
	spindle_init();
	parser_init();
	stepper_init();
	limits_init();
	

	printf("\n\t\t--  PP01 - 5 Axis CNC Controller  --\n");
	printf("\t\t-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	
	
	// Start the main loop
	char input[128];
	while(1)
	{
		printf("\n>>");
		fgets(input, sizeof(input), stdin);
		printf("%s",input);
		parse_line(input);
	
		#if DEBUG
			printf("Parameters:\n X%f Y%f Z%f A%f C%f I%f J%f K%f\nFeedrate: %f\n\n",parser_input.xyzac[0],parser_input.xyzac[1],parser_input.xyzac[2],parser_input.xyzac[3],parser_input.xyzac[4],parser_input.ijk[0],parser_input.ijk[1],parser_input.ijk[2],parser_input.feedrate);
			printf("State:\nPosition: X%f Y%f Z%f A%f C%f\nFeedrate: %.2f\nPlane: %d %d\nVertical: %d\n\n",parser_state.position[0],parser_state.position[1],parser_state.position[2],parser_state.position[3],parser_state.position[4],parser_state.feedrate,parser_state.plane[0],parser_state.plane[1],parser_state.axis_linear);
		#endif
	}
	
	
	for(;;);
	
	return 0;
}









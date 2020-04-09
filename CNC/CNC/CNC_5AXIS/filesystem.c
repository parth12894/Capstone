#include "CNC_5Axis.h"


uint8_t execute_from_sd_card(uint8_t file_num)
{
	static FATFS fs;
	static FIL file_object;
	FRESULT res;
	
	char line[128];
	char read_file_name[12];
	
	// Setup file.
	sprintf(read_file_name,"%d.txt", file_num);
	printf("\nReading from file '%s'", read_file_name);	
	
	// Wait card present and ready.
	if (SD_MMC_OK != sd_mmc_check(0))
		printf("\nPlease insert a FAT system SD card . . .\n\r");
	
	while(SD_MMC_OK != sd_mmc_check(0));
	
	// Mount Drive.
	f_mount(&fs, "", 0);
	delay_ms(1);
	
	// Open the text file.
	res = f_open(&file_object, (char const *)read_file_name, FA_READ);
	if (res)
	{
		puts("Error Opening File . . .");
		puts("Returning to terminal mode . . . \n");
		return (int)res;
	}
	
	puts("\nExecuting from the SD Card . . . ");
	
	// Executing from the SD Card till EOF.
	while (f_gets(line, sizeof line, &file_object)) 
	{
		printf("\n>> %s", line);

		parse_line(line);
		#if DEBUG
			printf("Parameters:\n X%f Y%f Z%f A%f C%f I%f J%f K%f\nFeedrate: %f\n\n",
				parser_input.xyzac[0],parser_input.xyzac[1],parser_input.xyzac[2],parser_input.xyzac[3],parser_input.xyzac[4],
				parser_input.ijk[0],parser_input.ijk[1],parser_input.ijk[2],
				parser_input.feedrate);
			
			printf("State:\nPosition: X%f Y%f Z%f A%f C%f\nFeedrate: %f\nPlane: %d %d\nVertical: %d\n\n",
				parser_state.position[0],parser_state.position[1],parser_state.position[2],parser_state.position[3],parser_state.position[4],
				parser_state.feedrate,parser_state.plane[0],parser_state.plane[1],parser_state.axis_linear);
		#endif

	}
	
	puts("\n\nFinished parsing from the SD Card, returning to terminal mode . . . \n");
	
	f_close(&file_object);	
	
	return 0;
}


#include "CNC_5Axis.h"

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
int i;
bool is_init = true;
static void button_on_PA11_pressed(void)
{
	if(is_init)
	{
		is_init = false;
		return;
	}
	i++;
	printf("\n%d",i);
	gpio_toggle_pin_level(LED);
	//delay_us(100);
	gpio_toggle_pin_level(LED);
}

int main_irq_test()
{
	atmel_start_init();

	
	printf("\n\t\t--  PP01 - 5 Axis CNC Controller  --\n");
	printf("\t\t-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	gpio_toggle_pin_level(LED);
	
	
	
	ext_irq_register(PIO_PA11_IDX, button_on_PA11_pressed);
	
	for(;;);
	
	return 0;
	
}
 
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
#define DATA_SIZE 2048
/* Read/write buffer */
static uint8_t data_buffer[DATA_SIZE];

static FRESULT scan_files(char *path)
{
	FRESULT res;
	FILINFO fno;
	DIR dir;
	int32_t i;
	char *pc_fn;
	#if _USE_LFN
	char c_lfn[_MAX_LFN + 1];
	fno.lfname = c_lfn;
	fno.lfsize = sizeof(c_lfn);
	#endif

	/* Open the directory */
	res = f_opendir(&dir, path);
	if (res == FR_OK) {
		i = strlen(path);
		for (;;) {
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0) {
				break;
			}

			#if _USE_LFN
			pc_fn = *fno.lfname ? fno.lfname : fno.fname;
			#else
			pc_fn = fno.fname;
			#endif
			if (*pc_fn == '.') {
				continue;
			}

			/* Check if it is a directory type */
			if (fno.fattrib & AM_DIR) {
				sprintf(&path[i], "/%s", pc_fn);
				res = scan_files(path);
				if (res != FR_OK) {
					break;
				}

				path[i] = 0;
				} else {
				printf("%s/%s\n\r", path, pc_fn);
			}
		}
	}

	return res;
}


uint8_t display_file_tree()
{
	FRESULT res;
	DIR dirs;
	TCHAR root_directory[3] = "0:";

	static FATFS fs;

	root_directory[0] = '0' + 0;

	/* Mount disk*/
	printf("-I1- Mount disk 0\n\r");
	/* Clear file system object */
	memset(&fs, 0, sizeof(FATFS));
	res = f_mount( &fs, "", 0);
	if (res != FR_OK)
	{
		printf("-E1- f_mount error code: 0x%d\n\r", res);
		return 0;
	}

	/* Test if the disk is formatted */
	res = f_opendir(&dirs, root_directory);
	if (res == FR_OK)
	{
		puts("-I2- The disk is properly formatted.\r");

		/* Display the file tree */
		puts("-I3- Displaying files contained in the memory :\r");
		strcpy((char *)data_buffer, root_directory);
		scan_files((char *)data_buffer);
	}else
	{
		printf("-E3- f_opendir error code: 0x%d\n\r", res);
		return 0;
	}
	
	/* Unmount disk */
	puts("-I11- Unmount disk\r");
	res = f_mount(NULL, "", 0);
	if (res != FR_OK)
	{
		printf("-E1- f_mount error code: 0x%d\n\r", res);
		return 0;
	}
	
	return 1;
}


uint8_t fatfs_example()
{
	FRESULT res;
	DIR dirs;
	TCHAR root_directory[3] = "0:";

	TCHAR write_file_name[12] = "write.txt";
	TCHAR read_file_name[12] = "read.txt";

	static FATFS fs;
	static FIL file_object;

	root_directory[0] = '0' + 0;

	/* Mount disk*/
	printf("-I1- Mount disk 0\n\r");
	/* Clear file system object */
	memset(&fs, 0, sizeof(FATFS));
	res = f_mount( &fs, "", 0);
	if (res != FR_OK)
	{
		printf("-E1- f_mount error code: 0x%d\n\r", res);
		return 0;
	}
	

	/* Test if the disk is formatted */
	res = f_opendir(&dirs, root_directory);
	if (res == FR_OK)
	{
		/* Erase sd card to reformat it ? */
		puts("-I2- The disk is already formatted.\r");

		/* Display the file tree */
		puts("-I3- Display files contained in the memory :\r");
		strcpy((char *)data_buffer, root_directory);
		scan_files((char *)data_buffer);
	} else if (res == FR_NO_FILESYSTEM)
	{

		/* Format disk */
		printf("-I5- Format disk 0\n\r");
		puts("-I6- Please wait a moment during formatting...\r");
		res = f_mkfs("", 0, 512);
		puts("-I7- Disk format finished !\r");
		if (res != FR_OK)
		{
			printf("-E2- f_mkfs error code: 0x%d\n\r", res);
			return 0;
		}

	} else if (FR_OK != res)
	{
		printf("-E3- f_opendir error code: 0x%d\n\r", res);
		return 0;
	}

	

	/* Create/write to a new file */
	printf("-I9- Create a file : \"%s\"\n\r", write_file_name);
	res = f_open(&file_object, (char const *)write_file_name, FA_CREATE_ALWAYS|FA_WRITE);
	if (res != FR_OK)
	{
		printf("-E4- f_open create error code: 0x%d\n\r", res);
		return 0;
	}
	
	
	f_printf(&file_object, "-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	f_puts("Done writing\0",&file_object);
	
	
	
	
	/* Read from a file */
	printf("-I9- Read a file : \"%s\"\n\r", read_file_name);
	res = f_open(&file_object,(char const *)read_file_name, FA_READ);
	if (res != FR_OK)
	{
		printf("-E4- f_open read error code: 0x%d\n\r", res);
		return 0;
	}
	
	char temp[128];
	while(!f_eof(&file_object))
	{
		puts("-------");
		f_gets(temp,128,&file_object);
		puts(temp);
		puts("-------");
	}




	/* Close the file */
	puts("-I11- Close file\r");
	res = f_close(&file_object);
	if (res != FR_OK)
	{
		printf("-E6- f_close error code: 0x%d\n\r", res);
		return 0;
	}
	
	/* Unmount disk */
	puts("-I11- Unmount disk\r");
	res = f_mount(NULL, "", 0);
	if (res != FR_OK)
	{
		printf("-E1- f_mount error code: 0x%d\n\r", res);
		return 0;
	}
	
	return 1;
}


void main_test_filesystem()
{
	printf("-- SD Card Example on FatFs --\n\r");
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	
	printf("Please plug an SD, MMC or SDIO card in slot.\n\r");

	/* Wait card present and ready */
	if (SD_MMC_OK != sd_mmc_check(0))
	{
		printf("Please insert a FAT system SD card . . .\n\r");
		while(SD_MMC_OK != sd_mmc_check(0)){}
	}
	
	
	fatfs_example();

	while (1){};

};

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define X_DIR1 0x2000000

void main_fast_GPIO_test()
{
	int hw, mask;
	
	mask = 1U << GPIO_PIN(X_DIR);
	printf(">>X_dir mask  %#0x \n", mask);
	hw = (uint32_t)PIOA + 0x3 * 0x200;
	printf(">>X_dir hw %#0x \n", hw);
	
	
	while(1)
	{
		hri_pio_set_ODSR_reg(PIOD, X_DIR1);
		//((Pio *)PIOD)->PIO_SODR = X_DIR1;
		//printf(">>X_dir is set\n");
		
		delay_us(10);
		
		hri_pio_clear_ODSR_reg(PIOD, X_DIR1);
		//((Pio *)PIOD)->PIO_CODR = X_DIR1;
		//printf(">>X_dir is clear\n");
		delay_us(10);
	}
	
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
int main_test_jason ()
{

	#if DEBUG_FILE
	//reset files
	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
	fp1 = fopen("C:\\Users\\Jason\\Downloads\\5AxisCNC\\xsegments.txt","w");
	fp2 = fopen("C:\\Users\\Jason\\Downloads\\5AxisCNC\\ysegments.txt","w");
	fp3 = fopen("C:\\Users\\Jason\\Downloads\\5AxisCNC\\zsegments.txt","w");
	fp4 = fopen("C:\\Users\\Jason\\Downloads\\5AxisCNC\\asegments.txt","w");
	fp5 = fopen("C:\\Users\\Jason\\Downloads\\5AxisCNC\\cegments.txt","w");
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	#endif

	char line[128];
	parser_init();
	while(1){
		
		#if DEBUG
		printf("Enter Something: \n");
		#endif
		
		fgets(line, sizeof(line), stdin);
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

	return (EXIT_SUCCESS);
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
uint32_t temp;
uint32_t j = 0;
uint32_t k = 50;

int flag = 0;


/**
 * Example of using TIMER_0.
 */
static struct timer_task TIMER_0_task1, TIMER_0_task2;

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level(DGI_GPIO0,HIGH);
	gpio_set_pin_level(C_STEP, true);

	j = (j + 1) % (10*25600);
	
	if(j==0)
	{
		
		//if(k <= 50)
			//flag = 1;
		//
		//if(k >= 100)
			//flag = 0;
		
			
		if(flag == 0)
		{	
			k = 35;
			flag = 1;
		}
		else
		{
			k = 200;
			flag = 0;
		}
			
		temp = (k * 19);
		//printf(">> %d\n", temp);
		timer_set_clock_cycles_per_tick(&TIMER_0,temp);
	}
	timer_add_task(&TIMER_1, &TIMER_0_task2);
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level(DGI_GPIO0,LOW);
	gpio_set_pin_level(C_STEP, false);
}

void TIMER_0_ex(void)
{
	TIMER_0_task1.interval = 1;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 1;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_ONE_SHOT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_start(&TIMER_0);
}

int main_test_dual_timers()
{
	atmel_start_init();
	
	flag = 0;
	
	printf("\n\t\t--  PP01 - 3+2 Axis CNC Controller  --\n");
	printf("\t\t-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	stepper_init();
	TIMER_0_ex();
	
	int i;
	for (i=0;i<60;i++)
		delay_ms(3000);
	
	printf("\n---Done---\n");
	
	timer_stop(&TIMER_0);
	
	for(;;);
	
	return 0;
};

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser(void)
{
	char str [256];
	char delim[] = " ";
	
	while (1)
	{
		printf ("Insert a g-code... ");
		gets (str);
		printf ("\nDecoding command: %s\n\n",str);
		
		char *ptr = strtok(str, delim);
		
		while(ptr != NULL)
		{
			printf("%s", ptr);
			
			if(strcmp(ptr, "G0") == 0)
			printf(": Rapid Linear Motion");
			else if(strcmp(ptr, "G1") == 0)
			printf(": Linear interpolation");
			else if(ptr[0] == 'F')
			printf(": Change feed rate");
			else if(ptr[0] == 'X')
			printf(": Move X axis");
			else if(ptr[0] == 'Y')
			printf(": Move Y axis");
			else if(ptr[0] == 'Z')
			printf(": Move Z axis");
			else if(strcmp(ptr, "M3") == 0)
			printf(": Turn on spindle");
			else if(strcmp(ptr, "M5") == 0)
			printf(": Turn off spindle");
			else
			printf(": Unknown word");
			
			
			
			printf("\n");
			ptr = strtok(NULL, delim);
		}
		
		printf("\n");
		printf("\n");
	}
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main_pwm_test()
{
	atmel_start_init();
	parser_init();
	stepper_init();
	parse_line("M9");
	

	printf("\n\t\t--  PP01 - 3+2 Axis CNC Controller  --\n");
	printf("\t\t-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	
	
	pwm_enable(&PWM_1);
	pwm_set_parameters(&PWM_1,PWM_PERIOD,886,0);
	for(;;);
	
	
	for(;;)
	{
		printf(">> dddd\n");
		
		pwm_set_parameters(&PWM_1,PWM_PERIOD,PWM_PERIOD-100,0);
		printf(">> ddddd\n");
		delay_ms(5000);
		pwm_set_parameters(&PWM_1,PWM_PERIOD,100,0);
		delay_ms(5000);
		
	}
	
	int i, l = 2000;
	
	while(1)
	{
		
		l = l+ 20;
		pwm_set_parameters(&PWM_1,l,1000,0);
		printf(">> %d\n",l);
		delay_ms(3000);

	}
	
	
	while(1)
	{
		for(i=0;i<12;i++)
		{
			l = l + 100;
			pwm_set_parameters(&PWM_1,2000,l,0);
			
		}
		
		for(i=0;i<12;i++)
		{
			l = l - 100;
			pwm_set_parameters(&PWM_1,2000,l,0);
			delay_ms(3000);
		}
	}
	
	for(;;);
	
	return 0;
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
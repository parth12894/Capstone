#include "CNC_5Axis.h"
 
void spindle_init()
{
	gpio_set_pin_direction(FLOOD_COOLANT, GPIO_DIRECTION_OUT);
	gpio_set_pin_function(FLOOD_COOLANT, GPIO_PIN_FUNCTION_OFF);
	gpio_set_pin_level(FLOOD_COOLANT, HIGH);
	
	gpio_set_pin_direction(MIST_COOLANT, GPIO_DIRECTION_OUT);
	gpio_set_pin_function(MIST_COOLANT, GPIO_PIN_FUNCTION_OFF);
	gpio_set_pin_level(MIST_COOLANT, HIGH);
	
	gpio_set_pin_direction(SPINDLE, GPIO_DIRECTION_OUT);
	gpio_set_pin_function(SPINDLE, GPIO_PIN_FUNCTION_OFF);
	gpio_set_pin_level(SPINDLE, HIGH);
	
	gpio_set_pin_direction(M4, GPIO_DIRECTION_OUT);
	gpio_set_pin_function(M4, GPIO_PIN_FUNCTION_OFF);
	gpio_set_pin_level(M4, HIGH);
	
}

void run_M_code(uint8_t code, float speed, uint32_t parameter)
{
	uint8_t i;
	
	#if DEBUG_ISR
		printf("\n===-> M%d\n", code);
	#endif
	
	switch(code)
	{
		case 3:
		case 4:
			gpio_set_pin_function(SPINDLE, MUX_PA12C_PWM1_PWMH0);
			pwm_enable(&PWM_1);
			pwm_set_parameters(&PWM_1,PWM_PERIOD,(int)23.2*speed,0);
			break;
		case 5:
			gpio_set_pin_direction(SPINDLE, GPIO_DIRECTION_OUT);
			gpio_set_pin_function(SPINDLE, GPIO_PIN_FUNCTION_OFF);
			gpio_set_pin_level(SPINDLE, HIGH);
			break;
		case 7:
			gpio_set_pin_level(MIST_COOLANT, LOW);
			//gpio_set_pin_level(FLOOD_COOLANT, HIGH);
			break;
		case 8:
			//gpio_set_pin_level(MIST_COOLANT, HIGH);
			gpio_set_pin_level(FLOOD_COOLANT, LOW);
			break;
		case 9:
			gpio_set_pin_level(MIST_COOLANT, HIGH);
			gpio_set_pin_level(FLOOD_COOLANT, HIGH);
			break;
		case 100:
			for(i = 0; i < parameter; i++)
			delay_us(1000);
			break;
	}
	
}
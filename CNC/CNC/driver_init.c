/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <hal_init.h>
#include <hpl_pmc.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hpl_pwm_base.h>

#include <hpl_pwm_base.h>

#include <hpl_tc.h>

#include <hpl_tc.h>

#include <hpl_usart_base.h>

struct timer_descriptor TIMER_0;
struct timer_descriptor TIMER_1;

struct mci_sync_desc IO_BUS;

struct pwm_descriptor PWM_0;

struct pwm_descriptor PWM_1;

struct calendar_descriptor CALENDER_INTERFACE;

struct usart_sync_descriptor TARGET_IO;

void IO_BUS_PORT_init(void)
{

	gpio_set_pin_direction(MCCDA,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCCDA,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(MCCDA,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(MCCDA,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <MUX_PA28C_HSMCI_MCCDA"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      MUX_PA28C_HSMCI_MCCDA);

	gpio_set_pin_direction(MCCK,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(MCCK,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(MCCK,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <MUX_PA25D_HSMCI_MCCK"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      MUX_PA25D_HSMCI_MCCK);

	gpio_set_pin_direction(MCDA0,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCDA0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(MCDA0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(MCDA0,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <MUX_PA30C_HSMCI_MCDA0"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      MUX_PA30C_HSMCI_MCDA0);

	gpio_set_pin_direction(MCDA1,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCDA1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(MCDA1,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(MCDA1,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <MUX_PA31C_HSMCI_MCDA1"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      MUX_PA31C_HSMCI_MCDA1);

	gpio_set_pin_direction(MCDA2,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCDA2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(MCDA2,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(MCDA2,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <MUX_PA26C_HSMCI_MCDA2"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      MUX_PA26C_HSMCI_MCDA2);

	gpio_set_pin_direction(MCDA3,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(MCDA3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(MCDA3,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(MCDA3,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <MUX_PA27C_HSMCI_MCDA3"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      MUX_PA27C_HSMCI_MCDA3);
}

void IO_BUS_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_HSMCI);
}

void IO_BUS_init(void)
{
	IO_BUS_CLOCK_init();
	mci_sync_init(&IO_BUS, HSMCI);
	IO_BUS_PORT_init();
}

void EXTERNAL_IRQ_1_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(DAC0, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DAC0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(DAC0, GPIO_PIN_FUNCTION_OFF);
}

void EXTERNAL_IRQ_0_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(Button, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(Button,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(Button, GPIO_PIN_FUNCTION_OFF);

	// Set pin direction to input
	gpio_set_pin_direction(A3, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A3,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A3, GPIO_PIN_FUNCTION_OFF);
}

void EXTERNAL_IRQ_3_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(A0, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A0, GPIO_PIN_FUNCTION_OFF);

	// Set pin direction to input
	gpio_set_pin_direction(A2, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A2,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A2, GPIO_PIN_FUNCTION_OFF);
}

void EXTERNAL_IRQ_2_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(A4, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A4,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A4, GPIO_PIN_FUNCTION_OFF);

	// Set pin direction to input
	gpio_set_pin_direction(A1, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A1,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A1, GPIO_PIN_FUNCTION_OFF);
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(PWM0_H1, MUX_PA24B_PWM0_PWMH1);

	gpio_set_pin_function(PWM0_H2, MUX_PA13B_PWM0_PWMH2);

	gpio_set_pin_function(PWM0_L0, MUX_PA1A_PWM0_PWML0);

	gpio_set_pin_function(PWM0_L3, MUX_PD27A_PWM0_PWML3);
}

void PWM_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_PWM0);
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, PWM0, _pwm_get_pwm());
}

void PWM_1_PORT_init(void)
{

	gpio_set_pin_function(PWM1_H0, MUX_PA12C_PWM1_PWMH0);

	gpio_set_pin_function(PWM1_L2, MUX_PA23D_PWM1_PWML2);
}

void PWM_1_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_PWM1);
}

void PWM_1_init(void)
{
	PWM_1_CLOCK_init();
	PWM_1_PORT_init();
	pwm_init(&PWM_1, PWM1, _pwm_get_pwm());
}

void CALENDER_INTERFACE_CLOCK_init(void)
{
}

void CALENDER_INTERFACE_init(void)
{
	CALENDER_INTERFACE_CLOCK_init();
	calendar_init(&CALENDER_INTERFACE, RTC);
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pmc_enable_periph_clock(ID_TC0_CHANNEL0);
	timer_init(&TIMER_0, TC0, _tc_get_timer());
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_1_init(void)
{
	_pmc_enable_periph_clock(ID_TC2_CHANNEL0);
	timer_init(&TIMER_1, TC2, _tc_get_timer());
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void TARGET_IO_PORT_init(void)
{

	gpio_set_pin_function(RX, MUX_PA21A_USART1_RXD1);

	gpio_set_pin_function(TX, MUX_PB4D_USART1_TXD1);
}

void TARGET_IO_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_USART1);
}

void TARGET_IO_init(void)
{
	TARGET_IO_CLOCK_init();
	TARGET_IO_PORT_init();
	usart_sync_init(&TARGET_IO, USART1, _usart_get_usart_sync());
}

void system_init(void)
{
	init_mcu();

	_pmc_enable_periph_clock(ID_PIOA);

	_pmc_enable_periph_clock(ID_PIOB);

	_pmc_enable_periph_clock(ID_PIOC);

	_pmc_enable_periph_clock(ID_PIOD);

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	/* GPIO on PA2 */

	gpio_set_pin_level(D7,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D7, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D7, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA5 */

	gpio_set_pin_level(D2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D2, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D2, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA6 */

	gpio_set_pin_level(D3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D3, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D3, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA9 */

	gpio_set_pin_level(DGI_GPIO0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(DGI_GPIO0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(DGI_GPIO0, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA10 */

	// Set pin direction to input
	gpio_set_pin_direction(A9, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A9,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A9, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA17 */

	gpio_set_pin_level(D8,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D8, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D8, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA18 */

	gpio_set_pin_level(D22,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D22, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D22, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA22 */

	// Set pin direction to input
	gpio_set_pin_direction(A10, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A10,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A10, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PA29 */

	gpio_set_pin_level(D30,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D30, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D30, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PB0 */

	gpio_set_pin_level(D15,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D15, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D15, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PB1 */

	gpio_set_pin_level(D14,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D14, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D14, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PB2 */

	// Set pin direction to input
	gpio_set_pin_direction(A15, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A15,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A15, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PB3 */

	// Set pin direction to input
	gpio_set_pin_direction(A14, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(A14,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(A14, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC8 */

	gpio_set_pin_level(LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LED, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC9 */

	gpio_set_pin_level(D9,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D9, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D9, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC12 */

	gpio_set_pin_level(D52,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D52, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D52, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC14 */

	gpio_set_pin_level(D53,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D53, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D53, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC16 */

	// Set pin direction to input
	gpio_set_pin_direction(CARD_DETECT_0, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(CARD_DETECT_0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(CARD_DETECT_0, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC19 */

	gpio_set_pin_level(D6,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D6, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D6, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD11 */

	gpio_set_pin_level(D5,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D5, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D5, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD15 */

	gpio_set_pin_level(D17,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D17, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D17, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD16 */

	gpio_set_pin_level(D16,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D16, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D16, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD17 */

	gpio_set_pin_level(D26,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D26, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D26, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD18 */

	gpio_set_pin_level(D19,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D19, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D19, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD19 */

	gpio_set_pin_level(D18,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D18, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D18, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD20 */

	gpio_set_pin_level(D12,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D12, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D12, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD21 */

	gpio_set_pin_level(D11,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D11, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D11, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD22 */

	gpio_set_pin_level(D13,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D13, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D13, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD25 */

	gpio_set_pin_level(D10,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D10, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D10, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PD28 */

	gpio_set_pin_level(D21,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(D21, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(D21, GPIO_PIN_FUNCTION_OFF);

	IO_BUS_init();
	EXTERNAL_IRQ_1_init();
	EXTERNAL_IRQ_0_init();
	EXTERNAL_IRQ_3_init();
	EXTERNAL_IRQ_2_init();

	PWM_0_init();

	PWM_1_init();

	CALENDER_INTERFACE_init();
	TIMER_0_init();
	TIMER_1_init();

	delay_driver_init();

	TARGET_IO_init();

	ext_irq_init();
}

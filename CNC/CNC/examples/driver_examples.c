/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static void button_on_PB13_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_1
 */
void EXTERNAL_IRQ_1_example(void)
{
	ext_irq_register(PIO_PB13_IDX, button_on_PB13_pressed);
}

static void button_on_PA11_pressed(void)
{
}
static void button_on_PA19_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{
	ext_irq_register(PIO_PA11_IDX, button_on_PA11_pressed);
	ext_irq_register(PIO_PA19_IDX, button_on_PA19_pressed);
}

static void button_on_PD26_pressed(void)
{
}
static void button_on_PD30_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_3
 */
void EXTERNAL_IRQ_3_example(void)
{
	ext_irq_register(PIO_PD26_IDX, button_on_PD26_pressed);
	ext_irq_register(PIO_PD30_IDX, button_on_PD30_pressed);
}

static void button_on_PC13_pressed(void)
{
}
static void button_on_PC31_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_2
 */
void EXTERNAL_IRQ_2_example(void)
{
	ext_irq_register(PIO_PC13_IDX, button_on_PC13_pressed);
	ext_irq_register(PIO_PC31_IDX, button_on_PC31_pressed);
}

static void period_cb_PWM_0(const struct pwm_descriptor *const descr)
{
	/* period interrupt */
}
/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_register_callback(&PWM_0, PWM_PERIOD_CB, period_cb_PWM_0);
	pwm_enable(&PWM_0);
}

static void period_cb_PWM_1(const struct pwm_descriptor *const descr)
{
	/* period interrupt */
}
/**
 * Example of using PWM_1.
 */
void PWM_1_example(void)
{
	pwm_register_callback(&PWM_1, PWM_PERIOD_CB, period_cb_PWM_1);
	pwm_enable(&PWM_1);
}

/**
 * Example of using CALENDER_INTERFACE.
 */
static struct calendar_alarm alarm;

static void alarm_cb(struct calendar_descriptor *const descr)
{
	/* alarm expired */
}

void CALENDER_INTERFACE_example(void)
{
	struct calendar_date date;
	struct calendar_time time;

	calendar_enable(&CALENDER_INTERFACE);

	date.year  = 2000;
	date.month = 12;
	date.day   = 31;

	time.hour = 12;
	time.min  = 59;
	time.sec  = 59;

	calendar_set_date(&CALENDER_INTERFACE, &date);
	calendar_set_time(&CALENDER_INTERFACE, &time);

	alarm.cal_alarm.datetime.time.sec = 4;
	alarm.cal_alarm.option            = CALENDAR_ALARM_MATCH_SEC;
	alarm.cal_alarm.mode              = REPEAT;

	calendar_set_alarm(&CALENDER_INTERFACE, &alarm, alarm_cb);
}

/**
 * Example of using TIMER_0.
 */
static struct timer_task TIMER_0_task1, TIMER_0_task2;

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

/**
 * Example of using TIMER_1.
 */
static struct timer_task TIMER_1_task1, TIMER_1_task2;

static void TIMER_1_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_1_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_1_example(void)
{
	TIMER_1_task1.interval = 100;
	TIMER_1_task1.cb       = TIMER_1_task1_cb;
	TIMER_1_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_1_task2.interval = 200;
	TIMER_1_task2.cb       = TIMER_1_task2_cb;
	TIMER_1_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_1, &TIMER_1_task1);
	timer_add_task(&TIMER_1, &TIMER_1_task2);
	timer_start(&TIMER_1);
}

void delay_example(void)
{
	delay_ms(5000);
}

/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 */
void TARGET_IO_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

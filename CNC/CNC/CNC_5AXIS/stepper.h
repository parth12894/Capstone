#ifndef STEPPER_H_
#define STEPPER_H_


#define ISR_EN() timer_start(&TIMER_1);

void ISR_init();

void stepper_init();

void ISR_disable();
#endif
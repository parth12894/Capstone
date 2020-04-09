#ifndef SPINDLE_H_
#define SPINDLE_H_

void spindle_init();

void run_M_code(uint8_t code, float speed, uint32_t parameter);

#endif
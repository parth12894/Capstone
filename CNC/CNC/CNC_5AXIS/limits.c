#include "CNC_5Axis.h"

extern struct timer_task stepper_ISR_task;



static void x_lim_pressed()
{
	ISR_disable();
	set_cord_to_zero(X_AXIS);
	return;
}

static void y_lim_pressed()
{
	ISR_disable();
	set_cord_to_zero(Y_AXIS);
	return;
}

static void z_lim_pressed()
{
	ISR_disable();
	set_cord_to_zero(Z_AXIS);
	return;
}

static void a_lim_pressed()
{
	ISR_disable();
	set_cord_to_zero(A_AXIS);
	return;
}



void limits_init()
{
	// Here 0x0F gives a value of 
	hri_pio_write_SCDR_reg(PIOD, 0x0F);
	hri_pio_set_IFSR_P26_bit(PIOD);
	hri_pio_set_IFSCSR_P26_bit(PIOD);
	ext_irq_register(PIO_PD26_IDX, x_lim_pressed);

	hri_pio_write_SCDR_reg(PIOC, 0x0F);
	hri_pio_set_IFSR_P31_bit(PIOC);
	hri_pio_set_IFSCSR_P31_bit(PIOC);
	ext_irq_register(PIO_PC31_IDX, y_lim_pressed);

	hri_pio_write_SCDR_reg(PIOD, 0x0F);
	hri_pio_set_IFSR_P30_bit(PIOD);
	hri_pio_set_IFSCSR_P30_bit(PIOD);
	ext_irq_register(PIO_PD30_IDX, z_lim_pressed);

	hri_pio_write_SCDR_reg(PIOA, 0x0F);
	hri_pio_set_IFSR_P19_bit(PIOA);
	hri_pio_set_IFSCSR_P19_bit(PIOA);
	ext_irq_register(PIO_PA19_IDX, a_lim_pressed);

	
	return;
}
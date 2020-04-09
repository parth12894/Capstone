#ifndef PIN_DEFINE_H_
#define PIN_DEFINE_H_

// SDMMC I/O
#define D33 MCDA2
#define D41	MCDA1
#define D44	MCCK
#define D48	MCDA0
#define D49 MCCDA


// USART for Serial Comm.
#define D46	RX
#define D47	TX


// PWM Outputs
#define D31 PWM0_L0 // GPIO 4
#define D45 PWM0_H1 // GPIO 2
#define D36 PWM0_H2 // M2
#define D20	PWM0_L3 // M4

#define D35 PWM1_H0 // M3
#define D43	PWM1_L2 // GPIO 3


// Analog Outputs
#define A12	DAC0	
#define A13	DAC1	// GPIO1


// Digital Outputs
#define OUT1	D12
#define ENABLE  D11
#define X_DIR   D10
#define X_STEP  D8
#define Y_DIR   D7
#define Y_STEP  D6
#define Z_DIR   D3
#define Z_STEP  D2
#define A_DIR   D14
#define A_STEP  D15
#define C_DIR	D16
#define C_STEP  D17


// Digital Inputs
#define X_LIM	A0
#define Y_LIM	A1
#define Z_LIM	A2
#define A_LIM	A3
#define C_LIM	A8


// Analog board connections
#define M1 D52		
#define M2 D36		// PWM0_H2
#define M3 D35		// PWM1_H0
#define M4 D20		// PWM0_L3

#define FLOOD_COOLANT M1
#define MIST_COOLANT M2
#define SPINDLE	M3

#define GPIO1 A13	// DAC1
#define GPIO2 D45	// PWM0_H1
#define GPIO3 D43	// PWM1_L2
#define GPIO4 D31	// PWM0_L0
#define GPIO5 D26

#endif
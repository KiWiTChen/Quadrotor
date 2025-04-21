#ifndef  __PPM_H_
#define  __PPM_H_

#include "PWM.h"

extern uint8_t Capture_Flag;
extern uint16_t Capture_val;
extern uint16_t Rc_Val[9];
extern uint16_t Data[8];

struct RC{
	uint16_t ROLL;
	uint16_t PITCH;
	uint16_t THROTTLE;
	uint16_t YAW;
	uint16_t AUX1;
	uint16_t AUX2;
	uint16_t AUX3;
	uint16_t AUX4;
};
extern struct RC Rc;


void PPM_Init(void);
void TIM5_IRQHandler(void);


#endif

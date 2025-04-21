#ifndef  __PPM_H_
#define  __PPM_H_
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


#endif

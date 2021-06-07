#ifndef __PWM_H 
#define __PWM_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"


void initPWM(void);
void setPWM(uint32_t ccr1);

#endif /* ifndef  */

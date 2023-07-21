#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include <math.h>

//设置一个定时器，中断采集数据
/*
	
TIM5	CH4		PA3
5ms 产生一个中断

*/

void TIMER_Init(void);

#endif

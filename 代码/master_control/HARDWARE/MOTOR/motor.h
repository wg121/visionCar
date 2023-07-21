#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
/*
	两个电机，4个io口
	PF->0 1 2 3 
*/

//PB输出
#define AIN1 PFout(0)
#define AIN2 PFout(1)
//
#define BIN1 PFout(2)
#define BIN2 PFout(3)

void MOTO_Init(void);
int GFP_abs(int p);
void Load(int motor1,int motor2);

//运动函数
void moto_advance(void);
void moto_left(void);
void moto_right(void);
void moto_back(void);
void moto_stop(void);

//小角度调整
void moto_small_left(void);
void moto_small_right(void);

#endif //__MOTOR_H

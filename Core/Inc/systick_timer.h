/*
 * systick_timer.h
 *
 *  Created on: 06-Oct-2020
 *      Author: pankaj.kumar
 */

#ifndef STM32F0308_DISCOVERY_SYSTICK_TIMER_H_
#define STM32F0308_DISCOVERY_SYSTICK_TIMER_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

typedef enum
{
	false = 0,
	true = 1
}bool;

extern bool;

typedef struct tStructure{
     int timerId;            //id to be assigned at run time
     uint32_t period;        //timer time in ms
     bool reload;            //to restart timer or not
     bool start;
     bool complete;
     uint32_t runningPeriod;
 }timerStruct;

 typedef struct List{
     timerStruct timer;
     struct List *nextTimer;
 }timerList;

 /*Function Prototypes*/
 bool startTimer(int *id, uint32_t time, bool reload);
 int isTimerComplete(int id);
 int isTimerStarted(int id);
 void enableSystemTimer(void);
 void delayMiliSec(int ms);
 void delayMicroSec(int us);
 bool stopTimer(int id);

#endif /* STM32F0308_DISCOVERY_SYSTICK_TIMER_H_ */

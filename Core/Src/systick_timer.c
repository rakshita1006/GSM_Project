/*
 * systick_timer.c
 *
 *  Created on: 06-Oct-2020
 *      Author: pankaj.kumar
 */
#include "systick_timer.h"
#include "stdlib.h"

timerList *masterTimerList;
static int delayTimer;

int searchTimerId(void)
{
    int id = 1;
    timerList *temp = masterTimerList;
    if(!temp)
        return id;
    else{
        while(temp->nextTimer != 0){
            temp = temp->nextTimer;
            id++;
        }
    }
    return ++id;
}

bool addTimer(int *id)
{
    timerList *temp = masterTimerList;
    timerList *timerptr = (timerList *)malloc(sizeof(timerList));
    if(!timerptr)
        return false;

    timerptr->timer.start = false;
    //search for timer id
    timerptr->timer.timerId = searchTimerId();
    *id = timerptr->timer.timerId;
    timerptr->nextTimer = 0;
    if(!masterTimerList){
        masterTimerList = timerptr;
    }
    else{       //add the node to the end of the list
        while(temp->nextTimer != 0)
            temp = temp->nextTimer;
        temp->nextTimer = timerptr;
    }
    return true;
}

bool startTimer(int *id, uint32_t time, bool reload)
{
    if(!*id){
        if(addTimer(id)==false)
            return false;
    }
    timerList *temp = masterTimerList;
    if(temp == 0)
        return false;
    while(temp->timer.timerId != *id){
        if(!temp->nextTimer)
            return false;
        temp = temp->nextTimer;
    }
    temp->timer.start = true;
    temp->timer.runningPeriod = 0;
    temp->timer.complete = false;
    temp->timer.period = time;
    temp->timer.reload = reload;
    return true;
}

bool stopTimer(int id)
{
    timerList *temp = masterTimerList;
    if(temp == 0)
        return false;
    while(temp->timer.timerId != id){
        if(!temp->nextTimer)
            return false;
        temp = temp->nextTimer;
    }
    temp->timer.start = false;
    return true;
}

int isTimerComplete(int id)
{
    timerList *temp = masterTimerList;
    if(temp == 0)
        return 0;
    while(temp->timer.timerId != id){
        if(!temp->nextTimer)
            return 0;
        temp = temp->nextTimer;
    }
    if(temp->timer.complete == true){
        temp->timer.complete = false;
        return 1;
    }
    else
        return 0;
}

int isTimerStarted(int id)
{
    timerList *temp = masterTimerList;
    if(temp == 0)
        return 0;
    while(temp->timer.timerId != id){
        if(!temp->nextTimer)
            return 0;
        temp = temp->nextTimer;
    }
    if(temp->timer.start == true)
    {
        return 1;
    }
    else
        return 0;
}

void delayMiliSec(int ms)
{
    startTimer(&delayTimer, ms, false);
    while(!isTimerComplete(delayTimer));
}


void HAL_SYSTICK_Callback(void)
{
	   if(!masterTimerList)
	        return;
	    timerList *temp = masterTimerList;
	    while(1){
	        if(temp->timer.start == true)
	            temp->timer.runningPeriod++;
	        if(temp->timer.runningPeriod >= temp->timer.period){
	            temp->timer.complete = true;
	            temp->timer.runningPeriod = 0;
	            if(temp->timer.reload == false)
	                temp->timer.start = false;
	        }
	        if(!temp->nextTimer)
	            return;
	        else
	            temp = temp->nextTimer;
	    }
}

/*
 * Software_Timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: 84859
 */
#include "Software_Timer.h"
int timer_counter[10];
int timer_flag[10];

void setTimer(int duration, int index){
	timer_counter[index] = duration/10;
	timer_flag[index] = 0;
}

void timerRun(){
	for(int i = 0; i<10; i++){ //TOI UU HOA ----> O(1)
	if(timer_counter[i] > 0){
		timer_counter[i]--;
		if(timer_counter[i] == 0){
			timer_flag[i] = 1;
		}
	}
}
}



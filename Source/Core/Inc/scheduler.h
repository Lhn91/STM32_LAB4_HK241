/*
 * scheduler.h
 *
 *  Created on: Nov 12, 2024
 *      Author: 84859
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct{
	void (*pTask)(void); //con tro ham
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
}sTasks;

#define SCH_MAX_TASKS 40

// scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Delete_Task(uint8_t TASK_INDEX);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Init(void);
void SCH_Go_To_Sleep(void);

#endif // SCHEDULER_H

#endif /* INC_SCHEDULER_H_ */

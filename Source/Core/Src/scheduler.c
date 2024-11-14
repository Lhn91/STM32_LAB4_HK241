/*
 * scheduler.c
 *
 *  Created on: Nov 12, 2024
 *      Author: 84859
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];  // Mảng lưu trữ các tác vụ
uint8_t current_index_task = 0;     // Biến quản lý trong mảng tác vụ

void SCH_Init(void) {
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Task(i);  // Xóa tất cả các tác vụ trong mảng
    }
}

uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    uint8_t Index = 0;

    // Tìm chỗ trống trong mảng
    while ((Index < SCH_MAX_TASKS) && (SCH_tasks_G[Index].pTask != 0)) {
        Index++;
    }

    // Nếu tìm thấy chỗ trống, thêm tác vụ vào mảng
    if (Index < SCH_MAX_TASKS) {
        SCH_tasks_G[Index].pTask = pFunction;
        SCH_tasks_G[Index].Delay = DELAY;
        SCH_tasks_G[Index].Period = PERIOD;
        SCH_tasks_G[Index].RunMe = 0;
    }

    // Trả về chỉ số (Index) của tác vụ trong mảng
    return Index;
}

void SCH_Update(void) {
    for (uint8_t Index = 0; Index < SCH_MAX_TASKS; Index++) {
        // Kiểm tra nếu có tác vụ tại vị trí này
        if (SCH_tasks_G[Index].pTask) {
            if (SCH_tasks_G[Index].Delay == 0) {
                // Đến thời gian thực thi tác vụ
                SCH_tasks_G[Index].RunMe += 1;  // Đánh dấu tác vụ cần được thực thi
                if (SCH_tasks_G[Index].Period) {
                    // Nếu tác vụ là định kỳ, đặt lại Delay cho lần tiếp theo
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            } else {
                // Giảm Delay nếu chưa đến thời gian thực thi
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}

void SCH_Dispatch_Tasks(void) {
    for (uint8_t Index = 0; Index < SCH_MAX_TASKS; Index++) {
        // Thực thi tác vụ nếu RunMe > 0
        if (SCH_tasks_G[Index].RunMe > 0) {
            (*SCH_tasks_G[Index].pTask)();    // Thực thi tác vụ
            SCH_tasks_G[Index].RunMe -= 1;    // Giảm cờ RunMe

            // Xóa tác vụ nếu là tác vụ một lần
            if (SCH_tasks_G[Index].Period == 0) {
                SCH_Delete_Task(Index);
            }
        }
    }

}

void SCH_Delete_Task(const uint8_t TASK_INDEX) {
    // Xóa tác vụ nếu vị trí hợp lệ
    if (TASK_INDEX < SCH_MAX_TASKS) {
        SCH_tasks_G[TASK_INDEX].pTask = 0;
        SCH_tasks_G[TASK_INDEX].Delay = 0;
        SCH_tasks_G[TASK_INDEX].Period = 0;
        SCH_tasks_G[TASK_INDEX].RunMe = 0;
    }
}

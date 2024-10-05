/*
 * RTOS_program.c
 *
 * Created: 2/3/2024 9:57:52 AM
 * Author: Kareem Hussein
 */

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GI_interface.h"

/* RTOS */
#include "RTOS_TMR_interface.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"

static Task_t arrayOfTasks[RTOS_TASK_NUM];

void RTOS_start(void)
{
    GI_voidEnable();
    RTOS_TMR_init();
    RTOS_TMR_setCompareMatchValue(249); // RTOS Tick >> 1ms
    RTOS_TMR_setCallBackCTC(&PRV_scheduler);
    RTOS_TMR_start();
}

void RTOS_createTask(u8 priority, u16 periodicity, void(*ptrToFun)(void))
{
    if((priority < RTOS_TASK_NUM) && (ptrToFun != NULL) && (arrayOfTasks[priority].pFunTask == NULL))
    {
        arrayOfTasks[priority].pFunTask        = ptrToFun;
        arrayOfTasks[priority].TaskPeriodicity = periodicity;
        arrayOfTasks[priority].TaskStatus      = RTOS_TASK_RESUMED;
    }
    else
    {
        // return Error State
    }
}

void RTOS_deleteTask(u8 priority)
{
    arrayOfTasks[priority].pFunTask = NULL;
}

void RTOS_suspendTask(u8 priority)
{
    arrayOfTasks[priority].TaskStatus = RTOS_TASK_SUSPENDED;
}

void RTOS_resumeTask(u8 priority)
{
    arrayOfTasks[priority].TaskStatus = RTOS_TASK_RESUMED;
}

static void PRV_scheduler(void)
{
    static u16 tickCount = 0;
    tickCount++;

    u8 highestPriorityIndex = RTOS_TASK_NUM; // Default to an invalid index
    u16 shortestPeriod = 0xFFFF; // Initialize to max possible value

    for (u8 taskCount = 0; taskCount < RTOS_TASK_NUM; taskCount++)
    {
        if (arrayOfTasks[taskCount].TaskStatus == RTOS_TASK_RESUMED)
        {
            // Check if the task is due to run
            if (tickCount % arrayOfTasks[taskCount].TaskPeriodicity == 0)
            {
                // Find the task with the shortest period (highest priority)
                if (arrayOfTasks[taskCount].TaskPeriodicity < shortestPeriod)
                {
                    shortestPeriod = arrayOfTasks[taskCount].TaskPeriodicity;
                    highestPriorityIndex = taskCount;
                }
            }
        }
    }

    // If a task is ready to run, execute it
    if (highestPriorityIndex < RTOS_TASK_NUM)
    {
        if (arrayOfTasks[highestPriorityIndex].pFunTask != NULL)
        {
            arrayOfTasks[highestPriorityIndex].pFunTask();
        }
    }
}

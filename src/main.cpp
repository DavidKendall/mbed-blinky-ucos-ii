#include <stdbool.h>
#include "mbed.h"
#include "ucos_ii.h"

/*
*********************************************************************************************************
*                                            APPLICATION TASK PRIORITIES
*********************************************************************************************************
*/

typedef enum {
  APP_TASK_LED1_PRIO = 4,
  APP_TASK_LED2_PRIO
} taskPriorities_t;

/*
*********************************************************************************************************
*                                            APPLICATION TASK STACKS
*********************************************************************************************************
*/

#define  APP_TASK_LED1_STK_SIZE              256
#define  APP_TASK_LED2_STK_SIZE              256

static OS_STK appTaskLED1Stk[APP_TASK_LED1_STK_SIZE];
static OS_STK appTaskLED2Stk[APP_TASK_LED2_STK_SIZE];

/*
*********************************************************************************************************
*                                            APPLICATION FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void appTaskLED1(void *pdata);
static void appTaskLED2(void *pdata);

/*
*********************************************************************************************************
*                                            GLOBAL TYPES AND VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            GLOBAL FUNCTION DEFINITIONS
*********************************************************************************************************
*/

int main() {
  /* Initialise the OS */
  OSInit();

  /* Create the tasks */
  OSTaskCreate(appTaskLED1,
               (void *)0,
               (OS_STK *)&appTaskLED1Stk[APP_TASK_LED1_STK_SIZE - 1],
               APP_TASK_LED1_PRIO);

  OSTaskCreate(appTaskLED2,
               (void *)0,
               (OS_STK *)&appTaskLED2Stk[APP_TASK_LED2_STK_SIZE - 1],
               APP_TASK_LED2_PRIO);


  /* Start the OS */
  OSStart();

  /* Should never arrive here */
  return 0;
}

/*
*********************************************************************************************************
*                                            APPLICATION TASK DEFINITIONS
*********************************************************************************************************
*/

static void appTaskLED1(void *pdata) {
  DigitalOut led1(LED1);
  DigitalOut led2(LED2);

  /* Start the OS ticker -- must be done in the highest priority task */
  SysTick_Config(SystemCoreClock / OS_TICKS_PER_SEC);

  led1 = 0;
  led2 = 1;
  /* Task main loop */
  while (true) {
    led1 = !led1;
    led2 = !led2;
    OSTimeDlyHMSM(0,0,0,500);
  }
}

static void appTaskLED2(void *pdata) {
  DigitalOut led2(LED2);

  while (true) {
    //led2 = !led2;
    OSTimeDlyHMSM(0,0,0,500);
  }
}



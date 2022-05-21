#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <stdint.h>
#include <OBDII.hpp>

// typedef enum  {
//   osOK                    =     0,       ///< function completed; no error or event occurred.
//   osEventSignal           =  0x08,       ///< function completed; signal event occurred.
//   osEventMessage          =  0x10,       ///< function completed; message event occurred.
//   osEventMail             =  0x20,       ///< function completed; mail event occurred.
//   osEventTimeout          =  0x40,       ///< function completed; timeout occurred.
//   osErrorParameter        =  0x80,       ///< parameter error: a mandatory parameter was missing or specified an incorrect object.
//   osErrorResource         =  0x81,       ///< resource not available: a specified resource was not available.
//   osErrorTimeoutResource  =  0xC1,       ///< resource not available within given time: a specified resource was not available within the timeout period.
//   osErrorISR              =  0x82,       ///< not allowed in ISR context: the function cannot be called from interrupt service routines.
//   osErrorISRRecursive     =  0x83,       ///< function called multiple times from ISR with same object.
//   osErrorPriority         =  0x84,       ///< system cannot determine priority or thread has illegal priority.
//   osErrorNoMemory         =  0x85,       ///< system is out of memory: it was impossible to allocate or reserve memory for the operation.
//   osErrorValue            =  0x86,       ///< value of a parameter is out of range.
//   osErrorOS               =  0xFF,       ///< unspecified RTOS error: run-time error but no other error message fits.
//   os_status_reserved      =  0x7FFFFFFF  ///< prevent from enum down-size compiler optimization.
// } osStatus;

// #define T_DISTANCE_TASK 300U

// /**
//   \brief   Get IPSR Register
//   \details Returns the content of the IPSR Register.
//   \return               IPSR Register value
//  */
// __attribute__( ( always_inline ) ) static inline uint32_t __get_IPSR(void)
// {
//   uint32_t result;

//   __asm volatile ("MRS %0, ipsr" : "=r" (result) );
//   return(result);
// }


// static __always_inline int inHandlerMode(void) {
//   return __get_IPSR() != 0;
// }

// static __always_inline uint32_t osKernelSysTick(void) {
//   return inHandlerMode() 
//     ? xTaskGetTickCountFromISR()
//     : xTaskGetTickCount();
// }

// static __always_inline osStatus osDelayUntil(uint32_t *prev_wake_time, uint32_t millis) {
//   TickType_t ticks = (millis / portTICK_PERIOD_MS);
//   vTaskDelayUntil((TickType_t *) prev_wake_time, ticks ? ticks : 1);

//   return osOK;
// }

// void taskOne(void *parameters) {
//   uint32_t wake_time = osKernelSysTick();
//   while (true) {
//     float distance = 10.14F;
//     vTaskDelay(150 / portTICK_PERIOD_MS);
//     osDelayUntil(&wake_time, T_DISTANCE_TASK);
//   }

//   vTaskDelete(NULL);
// }

void setup() {
  // xTaskCreate(taskOne, "taskOne", 1E4, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}
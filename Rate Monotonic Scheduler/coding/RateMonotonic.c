#include <avr/io.h> 
#include <util/delay.h> 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "RTOS_interface.h"
#include "RTOS_TMR_interface.h"


#define TASK1_PERIOD 100  // 100ms for Task 1
#define TASK2_PERIOD 200  // 200ms for Task 2
#define TASK3_PERIOD 500  // 500ms for Task 3

void task1();
void task2();
void task3();

int main(void) {
	DIO_voidSetPinDirection(PORTB, DIO_PIN0, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTB, DIO_PIN1, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTB, DIO_PIN2, DIO_PIN_OUTPUT);

	RTOS_TMR_init();
	
	RTOS_createTask(0, TASK1_PERIOD, task1);  // Task 1 with highest priority
	RTOS_createTask(1, TASK2_PERIOD, task2);  // Task 2 with medium priority 
	RTOS_createTask(2, TASK3_PERIOD, task3);  // Task 3 with lowest priority 

	RTOS_TMR_start();

	while (1) {
	task1();
	_delay_ms(TASK1_PERIOD);  
	task2();
	_delay_ms(TASK2_PERIOD);  
	task3();
	_delay_ms(TASK3_PERIOD);
	}
}

void task1() {
	DIO_voidTogglePinValue(PORTB, DIO_PIN0); 
}

void task2() {
	DIO_voidTogglePinValue(PORTB, DIO_PIN1);  
}

void task3() {
	DIO_voidTogglePinValue(PORTB, DIO_PIN2);  
}

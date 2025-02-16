/*
 * ultrasonic.h
 *
 *  Created on: Feb 4, 2025
 *      Author: sunbeam
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "main.h"

// Define ultrasonic sensor pins and timer
#define ULTRASONIC_TRIGGER_PORT     GPIOD
#define ULTRASONIC_TRIGGER_PIN      GPIO_PIN_11  // input pin

#define ULTRASONIC_ECHO_PIN_IC      &htim4 // output pin - Use the external reference


extern uint16_t distance;            // Declare as extern
extern uint8_t isReadingFinished;    // Declare as extern
extern uint8_t isRisingCaptured;     // Declare as extern
extern uint32_t InputCaptureValue_1; // Declare as extern
extern uint32_t InputCaptureValue_2; // Declare as extern
extern uint32_t InputCaptureDifference; // Declare as extern

// Function prototypes
void Ultrasonic_distance(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);


#endif /* INC_ULTRASONIC_H_ */

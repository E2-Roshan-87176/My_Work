/*
 * ultrasonic.c
 *
 *  Created on: Feb 4, 2025
 *      Author: sunbeam
 */

#include "ultrasonic.h"
#include"main.h"
uint8_t isRisingCaptured = 0;
uint32_t InputCaptureValue_1 = 0;
uint32_t InputCaptureValue_2 = 0;
uint32_t InputCaptureDifference = 0;

void Ultrasonic_distance(void)
{
    // Send Trigger Signal to ultrasonic trigger pin
    HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, GPIO_PIN_RESET);

    // Enable Timer counter
    __HAL_TIM_ENABLE_IT(ULTRASONIC_ECHO_PIN_IC, TIM_IT_CC1);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    // Capture Rising Edge
    if (isRisingCaptured == 0)
    {
        InputCaptureValue_1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
        isRisingCaptured = 1;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
    }
    // Capture Falling Edge
    else if (isRisingCaptured == 1)
    {
        InputCaptureValue_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
        __HAL_TIM_SET_COUNTER(&htim4, 0);

        if (InputCaptureValue_2 > InputCaptureValue_1)
        {
            InputCaptureDifference = InputCaptureValue_2 - InputCaptureValue_1;
        }
        else if (InputCaptureValue_1 > InputCaptureValue_2)
        {
            InputCaptureDifference = (0xFFFF - InputCaptureValue_1) + InputCaptureValue_2;
        }

        distance = InputCaptureDifference * 0.0173; // Convert to cm

        isReadingFinished = 1;

        isRisingCaptured = 0;

        __HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
        __HAL_TIM_DISABLE_IT(&htim4, TIM_IT_CC1);
    }
}


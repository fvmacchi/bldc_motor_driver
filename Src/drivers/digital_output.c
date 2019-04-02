/**
  ******************************************************************************
  * @file    digital_output.c
  * @author  Francesco Macchione
  * @brief   digital output abstraction layer.
  *          basically exists so you can reference a digital output without
  *          having to use two enums for the bank and pin
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "digital_output.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs ------------------------------------------------------------------*/

/* Private Function Declarations ---------------------------------------------*/

/* Private Data Declarations -------------------------------------------------*/

/* Private Functions ---------------------------------------------------------*/

/* Public Functions ----------------------------------------------------------*/

void digitalOutput_init(digitalOutput_handle_S * const handle, const digitalOutput_config_S config)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    HAL_GPIO_WritePin(config.GPIOx, config.pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = config.pin;
    if (config.openDrain)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    }
    else
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    }
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(config.GPIOx, &GPIO_InitStruct);

    handle->config = config;
}

bool digitalOutput_getState(const digitalOutput_handle_S * const handle)
{
    bool state = FALSE;
    if (handle != NULL)
    {
        if (HAL_GPIO_ReadPin(handle->config.GPIOx, handle->config.pin) == GPIO_PIN_SET)
        {
            state = TRUE;
        }
    }
    return state;
}

void digitalOutput_setState(const digitalOutput_handle_S * const handle, const bool state)
{
    if (handle != NULL)
    {
        HAL_GPIO_WritePin(handle->config.GPIOx, handle->config.pin, (state ? GPIO_PIN_SET : GPIO_PIN_RESET));
    }
}


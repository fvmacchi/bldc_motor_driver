/**
  ******************************************************************************
  * @file    digital_input.c
  * @author  Francesco Macchione
  * @brief   digital input abstraction layer.
  *          basically exists so you can reference a digital input without
  *          having to use two enums for the bank and pin
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "digital_input.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs ------------------------------------------------------------------*/

/* Private Function Declarations ---------------------------------------------*/

/* Private Data Declarations -------------------------------------------------*/

/* Private Functions ---------------------------------------------------------*/

/* Public Functions ----------------------------------------------------------*/

void digitalInput_init(digitalInput_handle_S * const handle, const digitalInput_config_S config)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = config.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

    switch (config.pull)
    {
        case DIGITAL_INPUT_PULL_NONE:
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;

        case DIGITAL_INPUT_PULL_UP:
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            break;

        case DIGITAL_INPUT_PULL_DOWN:
            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            break;

        default:
            // invalid
            break;
    }

    HAL_GPIO_Init(config.GPIOx, &GPIO_InitStruct);

    handle->config = config;
}

bool digitalInput_getState(const digitalInput_handle_S * const handle)
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

/**
  ******************************************************************************
  * @file    pin_configuration.c
  * @author  Francesco Macchione
  * @brief   configure micro pinouts
  */

/* Includes ------------------------------------------------------------------*/
#include "pin_configuration.h"
#include "hal.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs ------------------------------------------------------------------*/

/* Private Function Declarations ---------------------------------------------*/

/* Private Data Declarations -------------------------------------------------*/

/* Private Functions ---------------------------------------------------------*/

/* Public Functions ----------------------------------------------------------*/

void pinConfiguration_setup(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    __HAL_RCC_TIM17_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // TIM17 output
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM17;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // TIM1 outputs
    // GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    // HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    // GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    // HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

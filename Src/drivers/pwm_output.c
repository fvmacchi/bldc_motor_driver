/**
  ******************************************************************************
  * @file    pwm_output.c
  * @author  Francesco Macchione
  * @brief   pwm output abstraction layer
  */

/* Includes ------------------------------------------------------------------*/
#include "pwm_output.h"

#include "lib_math.h"

/* Defines -------------------------------------------------------------------*/

#define TIMER_SIZE_BITS (16U)

/* Typedefs ------------------------------------------------------------------*/

/* Private Function Declarations ---------------------------------------------*/

uint32_t pwmOutput_calculateDeadTime(const uint32_t deadTimeNS);

/* Private Data Declarations -------------------------------------------------*/

/* Private Functions ---------------------------------------------------------*/

uint32_t pwmOutput_calculateDeadTime(const uint32_t deadTimeNS)
{
    uint32_t deadTimeReg;
    const uint32_t clockPeriodNS = GIGA / SystemCoreClock;
    if (deadTimeNS < (0x80*clockPeriodNS))
    {
        deadTimeReg = deadTimeNS / clockPeriodNS;
    }
    else if (deadTimeNS < ((64U+0x40)*2*clockPeriodNS))
    {
        deadTimeReg = (deadTimeNS/(2*clockPeriodNS)) - 64U;
    }
    else if (deadTimeNS < ((32U+0x20)*8*clockPeriodNS))
    {
        deadTimeReg = (deadTimeNS/(8*clockPeriodNS)) - 32U;
    }
    else if (deadTimeNS < ((32U+0x20)*16*clockPeriodNS))
    {
        deadTimeReg = (deadTimeNS/(16*clockPeriodNS)) - 32U;
    }
    else
    {
        deadTimeReg = 0xFF;
    }
    return deadTimeReg;
}

/* Public Functions ----------------------------------------------------------*/

bool pwmBase_init(pwmBase_handle_S * const handle, const pwmBase_config_S config)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    bool ret = TRUE;

    handle->config = config;

    const uint32_t minFrequency = SystemCoreClock / (1<<TIMER_SIZE_BITS);
    uint32_t prescaler = 0;
    if (handle->config.frequencyHz <= minFrequency)
    {
        // keep in mind prescaler value is timerFrequency = clockFrequency / (prescaler + 1)
        prescaler = minFrequency / handle->config.frequencyHz;
    }

    const uint32_t period = (SystemCoreClock / (prescaler + 1)) / handle->config.frequencyHz;

    handle->htim.Instance = handle->config.timer;
    handle->htim.Init.Prescaler = prescaler;
    handle->htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    handle->htim.Init.Period = period;
    handle->htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    handle->htim.Init.RepetitionCounter = 0;
    handle->htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (HAL_TIM_Base_Init(&handle->htim) != HAL_OK)
    {
        ret = FALSE;
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&handle->htim, &sClockSourceConfig) != HAL_OK)
    {
        ret = FALSE;
    }
    if (HAL_TIM_PWM_Init(&handle->htim) != HAL_OK)
    {
        ret = FALSE;
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&handle->htim, &sMasterConfig) != HAL_OK)
    {
        ret = FALSE;
    }

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = pwmOutput_calculateDeadTime(handle->config.deadTimeNS);
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&handle->htim, &sBreakDeadTimeConfig) != HAL_OK)
    {
        ret = FALSE;
    }

    HAL_TIM_Base_Start(&handle->htim);

    return ret;
}

bool pwmOutput_init(pwmOutput_handle_S * const handle, const pwmOutput_config_S config, pwmBase_handle_S * const baseHandle)
{
    TIM_OC_InitTypeDef sConfigOC = {0};

    bool ret = TRUE;

    handle->config = config;
    handle->baseHandle = baseHandle;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&handle->baseHandle->htim, &sConfigOC, handle->config.timerOutputChannel) != HAL_OK)
    {
        ret = FALSE;
    }

    HAL_TIM_PWM_Start(&handle->baseHandle->htim, handle->config.timerOutputChannel);
    HAL_TIMEx_PWMN_Start(&handle->baseHandle->htim, handle->config.timerOutputChannel);

    return ret;
}

bool pwmOutput_setDuty(pwmOutput_handle_S * const handle, const _p15 percent)
{
    bool ret = FALSE;
    if (handle != NULL)
    {
        ret = TRUE;
        const uint16_t compare = (uint16_t)_P15Mul(percent, (_p15)handle->baseHandle->htim.Init.Period);
        // const uint32_t compare = (handle->baseHandle->htim.Init.Period * percent) / 100U;
        __HAL_TIM_SET_COMPARE(&handle->baseHandle->htim, handle->config.timerOutputChannel, compare);
    }
    return ret;
}

/**
  ******************************************************************************
  * @file    pwm_output.h
  * @author  Francesco Macchione
  * @brief   pwm output abstraction layer
  */

#ifndef PWM_OUTPUT_H
#define PWM_OUTPUT_H

/* Includes ------------------------------------------------------------------*/
#include "hal.h"
#include "lib_math.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs ------------------------------------------------------------------*/

typedef struct
{
    TIM_TypeDef * timer;
    uint32_t frequencyHz;
    uint32_t deadTimeNS;
} pwmBase_config_S;

typedef struct
{
    uint32_t timerOutputChannel;
} pwmOutput_config_S;

typedef struct
{
    pwmBase_config_S config;
    TIM_HandleTypeDef htim;
} pwmBase_handle_S;

typedef struct
{
    pwmOutput_config_S config;
    pwmBase_handle_S * baseHandle;
} pwmOutput_handle_S;

/* Public Function Declarations ----------------------------------------------*/

bool pwmBase_init(pwmBase_handle_S * const handle, const pwmBase_config_S config);
bool pwmOutput_init(pwmOutput_handle_S * const handle, const pwmOutput_config_S config, pwmBase_handle_S * const baseHandle);
bool pwmOutput_setDuty(pwmOutput_handle_S * const handle, const _p15 percent);

#endif // PWM_OUTPUT_H

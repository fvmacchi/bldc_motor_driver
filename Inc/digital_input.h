/**
  ******************************************************************************
  * @file    digital_input.h
  * @author  Francesco Macchione
  * @brief   digital input abstraction layer.
  *          basically exists so you can reference a digital input without
  *          having to use two enums for the bank and pin
  *
  */

#ifndef DIGITAL_INPUT_H
#define DIGITAL_INPUT_H

/* Includes ------------------------------------------------------------------*/
#include "hal.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs ------------------------------------------------------------------*/

typedef enum
{
	DIGITAL_INPUT_PULL_NONE,
	DIGITAL_INPUT_PULL_UP,
	DIGITAL_INPUT_PULL_DOWN,
} digitalInput_pull_E;

typedef struct
{
	GPIO_TypeDef * GPIOx;
	uint32_t pin;
	digitalInput_pull_E pull;
} digitalInput_config_S;

typedef struct
{
	digitalInput_config_S config;
} digitalInput_handle_S;

/* Public Function Declarations ----------------------------------------------*/

void digitalInput_init(digitalInput_handle_S * const handle, const digitalInput_config_S config);
bool digitalInput_getState(const digitalInput_handle_S * const handle);

#endif // DIGITAL_INPUT_H

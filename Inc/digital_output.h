/**
  ******************************************************************************
  * @file    digital_output.h
  * @author  Francesco Macchione
  * @brief   digital output abstraction layer.
  *          basically exists so you can reference a digital output without
  *          having to use two enums for the bank and pin
  *
  */

#ifndef DIGITAL_OUTPUT_H
#define DIGITAL_OUTPUT_H

/* Includes ------------------------------------------------------------------*/
#include "hal.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs ------------------------------------------------------------------*/

typedef struct
{
	GPIO_TypeDef * GPIOx;
	uint32_t pin;
	bool openDrain;
} digitalOutput_config_S;

typedef struct
{
	digitalOutput_config_S config;
} digitalOutput_handle_S;

/* Public Function Declarations ----------------------------------------------*/

void digitalOutput_init(digitalOutput_handle_S * const handle, const digitalOutput_config_S config);
bool digitalOutput_getState(const digitalOutput_handle_S * const handle);
void digitalOutput_setState(const digitalOutput_handle_S * const handle, const bool state);

#endif // DIGITAL_OUTPUT_H

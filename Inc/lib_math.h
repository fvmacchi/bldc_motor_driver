/**
  ******************************************************************************
  * @file    lib_math.h
  * @author  Francesco Macchione
  * @brief   general math helpers
  */

#ifndef LIB_MATH_H
#define LIB_MATH_H

// #define ARM_MATH_CM0 // Used in arm_math.h

/* Includes ------------------------------------------------------------------*/
#include "hal.h"

/* Defines -------------------------------------------------------------------*/

#define KILO (1000U)
#define MEGA (KILO*KILO)
#define GIGA (MEGA*KILO)

// 15 bit percentage (16th bit used for 100%)
#define _P15(X) (X*(1<<15))

// #define _Q31(X) ((q31_t)(X*(1<<31)))

// #define _Q(X) (_Q31(X))

// #define _Qmul(N1,N2,DES) ()

/* Typedefs ------------------------------------------------------------------*/

typedef uint16_t _p15;

/* Public Function Declarations ----------------------------------------------*/

inline _p15 _P15Mul(const _p15 x, const _p15 y)
{
    return (_p15)(((uint32_t)x) * ((uint32_t)y) / (1 << 15));
}

#endif // LIB_MATH_H

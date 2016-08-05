#pragma once

#include "cstdint.h"

extern uint32_t ticks;

class Time
{
  public:
    static void Reset(void);
    static uint32_t GetTime(void);
    static void Tick(void);
};

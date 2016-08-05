#pragma once

#include "cstdint.h"
#include "support.h"

#define MAX_WORKERS 128
class List
{
  public:
    List();
    bool Append(Support* s);
    Support* Remove(uint32_t idx);
    Support* Get(uint32_t idx);
    uint32_t Length();
  private:
    Support* data[MAX_WORKERS];
    uint32_t size;
    uint32_t cap;
};

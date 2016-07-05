#pragma once
#include "charter.h"

void sparks(data_package);

double spark_divisor(uint32 max, 
                     uint32 min, 
                     uint32 sparkle_count);

uint32 spark_pick_index(uint32 datum,
                        uint32 min,
                        double divisor);

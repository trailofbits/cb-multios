#pragma once
#include "cgc_charter.h"

void cgc_sparks(data_package);

double cgc_spark_divisor(uint32 max, 
                     uint32 min, 
                     uint32 cgc_sparkle_count);

uint32 cgc_spark_pick_index(uint32 datum,
                        uint32 min,
                        double divisor);

#pragma once
#include "charter.h"
void bars(data_package);

double bar_scale_factor(uint32 column_count, uint32 max_value);
uint32 bar_use_columns(uint32 datum, double scale_factor, uint32 column_count);

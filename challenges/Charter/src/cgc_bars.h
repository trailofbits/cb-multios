#pragma once
#include "cgc_charter.h"
void cgc_bars(data_package);

double cgc_bar_scale_factor(uint32 column_count, uint32 max_value);
uint32 cgc_bar_use_columns(uint32 datum, double scale_factor, uint32 column_count);

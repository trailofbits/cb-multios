#pragma once
#include "cgc_charter.h"
#include "cgc_block.h"

void cgc_each(data_package, void (^block)(uint32 cgc_index, uint32 value));


#pragma once

#include "types.h"

#define RANDOM_PAGE_ADDRESS 0x4347C000
#define RANDOM_PAGE_LENGTH 0x1000

void monte_initialize();
float64 monte_initialize_step(float64 first, uint64 second);

void monte_adjust(float64 new_splatter, float64 new_scaler);

uint8 monte_happy();

float64 monte_state();
float64 monte_state_step(float64 running, float64 cur);

float64 monte_gen();

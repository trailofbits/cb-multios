#pragma once

#include "cgc_types.h"

#define RANDOM_PAGE_ADDRESS 0x4347C000
#define RANDOM_PAGE_LENGTH 0x1000

void cgc_monte_initialize();
float64 monte_initialize_step(float64 first, uint64 second);

void cgc_monte_adjust(float64 new_splatter, float64 new_scaler);

uint8 cgc_monte_happy();

float64 monte_state();
float64 monte_state_step(float64 running, float64 cur);

float64 cgc_monte_gen();

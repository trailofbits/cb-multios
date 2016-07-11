#include <stdint.h>

/*

sampling frequency: 8000 Hz

fixed point precision: 16 bits

* 0 Hz - 1400 Hz
  gain = 0
  desired attenuation = -30 dB
  actual attenuation = n/a

* 1600 Hz - 2200 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 2400 Hz - 4000 Hz
  gain = 0
  desired attenuation = -30 dB
  actual attenuation = n/a

*/

#define BANDPASS_COUNT 17

static int16_t BANDPASS_COEFFS[BANDPASS_COUNT] = {
  2468,
  -3051,
  -4673,
  1604,
  5658,
  -1655,
  -7341,
  547,
  7776,
  547,
  -7341,
  -1655,
  5658,
  1604,
  -4673,
  -3051,
  2468
};


/*

sampling frequency: 8000 Hz

fixed point precision: 16 bits

* 0 Hz - 300 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 500 Hz - 4000 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define LOWPASS_COUNT 45

static int16_t LOWPASS_COEFFS [LOWPASS_COUNT] = {
  -497,
  -410,
  -542,
  -668,
  -773,
  -839,
  -848,
  -782,
  -626,
  -369,
  -4,
  467,
  1037,
  1691,
  2407,
  3156,
  3905,
  4620,
  5264,
  5806,
  6215,
  6470,
  6557,
  6470,
  6215,
  5806,
  5264,
  4620,
  3905,
  3156,
  2407,
  1691,
  1037,
  467,
  -4,
  -369,
  -626,
  -782,
  -848,
  -839,
  -773,
  -668,
  -542,
  -410,
  -497
};


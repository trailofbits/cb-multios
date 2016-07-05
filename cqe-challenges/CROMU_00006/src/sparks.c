#include <libcgc.h>
#include "libc.h"
#include "charter.h"
#include "sparks.h"
#include "data.h"
#include "block.h"

uint32* sparkles = NULL;
uint32 sparkle_count = 0;

void sparks(data_package data) {
  uint32 candidate_count;

  uint32 bar_buf[data.size];
  __block uint32* bar_buf_ptr = (uint32*)bar_buf;

  read(&candidate_count, sizeof(candidate_count));

  if ((candidate_count == 0 && sparkle_count == 0) ||
   (candidate_count > MAX_ALLOCATE_SIZE)) {
    _terminate(-1);
  }

  if (candidate_count != 0) {
    if (sparkles != NULL) {
      deallocate(sparkles, sparkle_count );
    }

    sparkle_count = candidate_count;

#ifdef PATCHED
    int alloc_error = allocate( (candidate_count + 1)*4, 0, (void**)&sparkles);
#else
    int alloc_error = allocate(candidate_count + 1, 0, (void**)&sparkles);
#endif

    if (alloc_error) _terminate(-1);

    for (uint32 cur = 0; cur < sparkle_count; cur++) {
      uint32 sparkle;
      read(&sparkle, sizeof(sparkle));
      sparkles[cur] = sparkle;
    }
  }

  __block uint32 min = UINT32_MAX;
  __block uint32 max = 0;

  each(data, ^(uint32 idx, uint32 datum){
      if (datum > max) max = datum;
      if (datum < min) min = datum;
    });

  if (min == max) {
    each(data, ^(uint32 cur, uint32 datum) {
        bar_buf_ptr[cur] = sparkles[sparkle_count - 1];
      });
  } else {
    double div = spark_divisor(max, min, sparkle_count);
    
    each(data, ^(uint32 cur, uint32 datum){
        uint32 idx = spark_pick_index(datum, min, div);
      
        bar_buf_ptr[cur] = sparkles[idx];
      });
  }

  transmit_all(STDOUT, (char*)(bar_buf), data.size * sizeof(uint32));

  return;  
}

double spark_divisor(uint32 max, 
                     uint32 min, 
                     uint32 sparkle_count) {
  return ((double)max - (double)min) / (sparkle_count - 1);
  }

uint32 spark_pick_index(uint32 datum,
                        uint32 min,
                        double divisor) {
  return (uint32)(((double)datum - min) / divisor);
}

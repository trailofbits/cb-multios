#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_charter.h"
#include "cgc_sparks.h"
#include "cgc_data.h"
#include "cgc_block.h"

uint32* cgc_sparkles = NULL;
uint32 sparkle_count = 0;

void cgc_sparks(data_package data) {
  uint32 candidate_count;

  uint32 bar_buf[data.size];
  __block uint32* bar_buf_ptr = (uint32*)bar_buf;

  cgc_read(&candidate_count, sizeof(candidate_count));

  if ((candidate_count == 0 && sparkle_count == 0) ||
   (candidate_count > MAX_ALLOCATE_SIZE)) {
    cgc__terminate(-1);
  }

  if (candidate_count != 0) {
    if (cgc_sparkles != NULL) {
      cgc_deallocate(cgc_sparkles, sparkle_count );
    }

    sparkle_count = candidate_count;

#ifdef PATCHED
    int alloc_error = cgc_allocate( (candidate_count + 1)*4, 0, (void**)&cgc_sparkles);
#else
    int alloc_error = cgc_allocate(candidate_count + 1, 0, (void**)&cgc_sparkles);
#endif

    if (alloc_error) cgc__terminate(-1);

    for (uint32 cur = 0; cur < sparkle_count; cur++) {
      uint32 sparkle;
      cgc_read(&sparkle, sizeof(sparkle));
      cgc_sparkles[cur] = sparkle;
    }
  }

  __block uint32 min = UINT32_MAX;
  __block uint32 max = 0;

  cgc_each(data, ^(uint32 idx, uint32 datum){
      if (datum > max) max = datum;
      if (datum < min) min = datum;
    });

  if (min == max) {
    cgc_each(data, ^(uint32 cur, uint32 datum) {
        bar_buf_ptr[cur] = cgc_sparkles[sparkle_count - 1];
      });
  } else {
    double div = cgc_spark_divisor(max, min, sparkle_count);
    
    cgc_each(data, ^(uint32 cur, uint32 datum){
        uint32 idx = cgc_spark_pick_index(datum, min, div);
      
        bar_buf_ptr[cur] = cgc_sparkles[idx];
      });
  }

  cgc_transmit_all(STDOUT, (char*)(bar_buf), data.size * sizeof(uint32));

  return;  
}

double cgc_spark_divisor(uint32 max, 
                     uint32 min, 
                     uint32 sparkle_count) {
  return ((double)max - (double)min) / (sparkle_count - 1);
  }

uint32 cgc_spark_pick_index(uint32 datum,
                        uint32 min,
                        double divisor) {
  return (uint32)(((double)datum - min) / divisor);
}

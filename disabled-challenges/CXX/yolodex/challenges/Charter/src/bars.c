#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_bars.h"
#include "cgc_rand.h"
#include "cgc_data.h"

void cgc_draw_bars(data_package, uint32, uint32, uint32);
void cgc_draw_row(char* chart_row_ptr, uint32 bar_character, uint32 use_columns);

void cgc_bars(data_package data) {
  uint32 max_value, column_count, bar_character;

  cgc_read(&max_value, sizeof(max_value));
  cgc_read(&column_count, sizeof(column_count));
  cgc_read(&bar_character, sizeof(bar_character));

  cgc_draw_bars(data, max_value, column_count, bar_character);
}

void cgc_draw_bars(data_package data, 
               uint32 max_value, 
               uint32 column_count, 
               uint32 bar_character) {
  if (column_count > (MAX_STACK_SIZE / 4)) {
    cgc__terminate(-1);
  }
  cgc_size_t row_size = (column_count * 4) + 16;
  row_size = row_size - (row_size % 16);
  char chart_row[row_size];

  __block char* chart_row_ptr = (char*)(chart_row + 0);

  double scale_factor = cgc_bar_scale_factor(column_count, max_value);

  uint32 scrambler = cgc_rand();
  scrambler %= 4;
  scrambler++;

  scale_factor *= scrambler;

  cgc_each(data, ^(uint32 cur, uint32 datum) {
      uint32 use_columns = cgc_bar_use_columns(datum, scale_factor, column_count);

    cgc_draw_row(chart_row_ptr, bar_character, use_columns);
    cgc_transmit_all(STDOUT, chart_row_ptr, use_columns + 1);
    });
}

double cgc_bar_scale_factor(uint32 column_count, uint32 max_value) {
  return (double)column_count / (double)max_value;
}

uint32 cgc_bar_use_columns(uint32 datum, double scale_factor, uint32 column_count) {
  uint32 use_columns = (uint32)((double) datum * scale_factor);
  
#ifdef PATCHED
  if (use_columns > column_count) use_columns = column_count;
#endif

  return use_columns;
}

void cgc_draw_row(char* chart_row_ptr, uint32 bar_character, uint32 use_columns) {
  for (uint32 column = 0; column <= use_columns + 1; column++) {
    char fill = '\n';
    if (column < use_columns) fill = bar_character;
    
    chart_row_ptr[column] = fill;
  }
}

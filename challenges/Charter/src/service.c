#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_charter.h"
#include "cgc_bars.h"
#include "cgc_sparks.h"
#include "cgc_rand.h"
#include "cgc_data.h"

void cgc_echo();
void cgc_sparks(data_package);
void cgc_read_data(uint32);

int main(int cgc_argc, char *cgc_argv[]) {
  uint32 datum_count;

  cgc_read(&datum_count, sizeof(datum_count));
  if ((datum_count < 1) || (datum_count > MAX_STACK_SIZE)) return -1;

  cgc_read_data(datum_count);

  return 0;
}

void cgc_read_data(uint32 datum_count) {
  uint32 data[datum_count];
  data_package pack = {datum_count, data};

  for (uint32 cur = 0; cur < datum_count; cur++) {
    uint32 datum;
    cgc_read(&datum, sizeof(datum));
    data[cur] = datum;
  }

  while(1) {
    cgc_transmit_all(STDOUT, "CHRT", 4);
    cgc_transmit_all(STDOUT, (char*)(&datum_count), 4);

    uint32 choice;
    cgc_read(&choice, sizeof(choice));
    
    switch(choice) {
    case 1:
      cgc_sparks(pack);
      break;
    case 3:
      cgc_bars(pack);
      break;
    case 4:
      cgc_echo();
      break;
    case 5:
      cgc_seed();
      break;
    case 6:
      cgc_noise();
      break;
    case 7:
      cgc_replacer(pack);
      break;
    default:
      cgc__terminate(0);
    }
  }
}

void cgc_draw_echo(uint32 count) {
  uint32 body[count];

  for (uint32 cur = 0; cur < count; cur++) {
    uint32 chr;
    cgc_read(&chr, sizeof(chr));
    body[cur] = chr;
  }

  cgc_transmit_all(STDOUT, (char*)(body), count * sizeof(uint32));
}

void cgc_echo() {
  uint32 count;
  cgc_read(&count, sizeof(count));

  if ((count < 1) || (count > MAX_STACK_SIZE)) cgc__terminate(-1);

  cgc_draw_echo(count);
}

cgc_size_t cgc_read(void* buf, cgc_size_t expected_size) {
  cgc_size_t actual_size;
  int status;

  status = cgc_receive(STDIN, buf, expected_size, &actual_size);

  if (status != 0) cgc__terminate(-1);
  if (actual_size != expected_size) cgc__terminate(-1);

  return actual_size;
}

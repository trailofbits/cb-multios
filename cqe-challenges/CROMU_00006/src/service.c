#include <libcgc.h>
#include "libc.h"
#include "charter.h"
#include "bars.h"
#include "sparks.h"
#include "rand.h"
#include "data.h"

void echo();
void sparks(data_package);
void read_data(uint32);

int main(void) {
  uint32 datum_count;

  read(&datum_count, sizeof(datum_count));
  if ((datum_count < 1) || (datum_count > MAX_STACK_SIZE)) return -1;

  read_data(datum_count);

  return 0;
}

void read_data(uint32 datum_count) {
  uint32 data[datum_count];
  data_package pack = {datum_count, data};

  for (uint32 cur = 0; cur < datum_count; cur++) {
    uint32 datum;
    read(&datum, sizeof(datum));
    data[cur] = datum;
  }

  while(1) {
    transmit_all(STDOUT, "CHRT", 4);
    transmit_all(STDOUT, (char*)(&datum_count), 4);

    uint32 choice;
    read(&choice, sizeof(choice));
    
    switch(choice) {
    case 1:
      sparks(pack);
      break;
    case 3:
      bars(pack);
      break;
    case 4:
      echo();
      break;
    case 5:
      seed();
      break;
    case 6:
      noise();
      break;
    case 7:
      replacer(pack);
      break;
    default:
      _terminate(0);
    }
  }
}

void draw_echo(uint32 count) {
  uint32 body[count];

  for (uint32 cur = 0; cur < count; cur++) {
    uint32 chr;
    read(&chr, sizeof(chr));
    body[cur] = chr;
  }

  transmit_all(STDOUT, (char*)(body), count * sizeof(uint32));
}

void echo() {
  uint32 count;
  read(&count, sizeof(count));

  if ((count < 1) || (count > MAX_STACK_SIZE)) _terminate(-1);

  draw_echo(count);
}

size_t read(void* buf, size_t expected_size) {
  size_t actual_size;
  int status;

  status = receive(STDIN, buf, expected_size, &actual_size);

  if (status != 0) _terminate(-1);
  if (actual_size != expected_size) _terminate(-1);

  return actual_size;
}

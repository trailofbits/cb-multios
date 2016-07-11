#include "data.h"

void each(data_package data, void (^block)(uint32 index, uint32 value)) {
  for(uint32 cur = 0; cur < data.size; cur++) {
    block(cur, data.contents[cur]);
  }
}

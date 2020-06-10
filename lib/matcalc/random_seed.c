#include <bsd/stdlib.h>

#include "random_seed.h"


uint32_t u32rand() {
  return arc4random();
}

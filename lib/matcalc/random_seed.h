#ifndef RANDOM_SEED_H_YRDGPAOB
#define RANDOM_SEED_H_YRDGPAOB

#include <stdint.h>

#if defined(__linux__)
  typedef unsigned char u_char;
  #include <bsd/stdlib.h>
#elif defined(__APPLE__)
  #include <stdlib.h>
#else
  #include <sys/param.h>
  #if defined(BSD)
    #include <stdlib.h>
  #endif
#endif

uint32_t u32rand();


#endif /* end of include guard: RANDOM_SEED_H_YRDGPAOB */

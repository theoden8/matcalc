#ifndef RANDOM_SEED_H_YRDGPAOB
#define RANDOM_SEED_H_YRDGPAOB

#include <stdint.h>

#if defined(__linux__)
  #include <bsd/stdlib.h>
#elif defined(__unix__)
  #if defined(__APPLE__) || defined(__MACH__)
    #include <stdlib.h>
  #else
    #include <sys/param.h>
    #if defined(BSD)
      #include <stdlib.h>
    #endif
  #endif
#endif

uint32_t u32rand();


#endif /* end of include guard: RANDOM_SEED_H_YRDGPAOB */

#include "bells.h"

// bells numbers:
//  the number of ways to partition a set of n elements
//
// computing:
//
// B[0] = B[1] = 1
// (1) using binomial coefficients:
//   B[n] = sum ( C_n^k | k <- [0..n-1] )
// (2) using stirling numbers of second kind:
//   B[n] = sum ( S2_n^k | k <- [0..n] )
// (3) using Bell's triangle
//    1               // base
//    1  2            // copy 1, add 1 + 1 = 2
//    2  3  5         // copy 2 to 2, add 1 + 2 = 3, add 2 + 3 = 5
//    5  7  10 15
//    15 20 27 37 52
//  *1 *2 3 *5 7 10 *15 20 27 37 *52

void calc_bells(size_t n, mpz_visitor visitor_func) {
  {
    mpz_t b;
    mpz_init(b);
    mpz_set_si(b, 1);
    if(n > 1) visitor_func(&b);
    if(n > 2) visitor_func(&b);
    mpz_set_si(b, 2);
    if(n > 3) visitor_func(&b);
    mpz_clear(b);
    if(n <= 3) return;
  }

  const size_t ROW_SIZE = n - 2;
  mpz_t *buf = malloc(sizeof(mpz_t) * ROW_SIZE * 2);
  assert(buf != NULL);
  for(int i = 0; i < n - 2; ++i) {
    mpz_inits(buf[i], buf[ROW_SIZE + i], NULL);
  }
  mpz_set_si(buf[0], 1);
  mpz_set_si(buf[1], 2);
  for(size_t r = 3-1; r < n; ++r) {
    const int parity = (r + 1) & 1;
    const int invparity = parity ^ 1;
    const int OFFA = parity * ROW_SIZE;
    const int OFFB = invparity * ROW_SIZE;
    mpz_set(buf[OFFA], buf[OFFB + r - 2]);
    for(int c = 1; c < r; ++c) {
      mpz_add(buf[OFFA + c], buf[OFFB + c - 1], buf[OFFA + c - 1]);
    }
    visitor_func(&buf[OFFA + r - 1]);
  }
  for(int i = 0; i < n - 2; ++i) {
    mpz_clears(buf[i], buf[ROW_SIZE + i], NULL);
  }
  free(buf);
}

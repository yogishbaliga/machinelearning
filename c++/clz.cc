#include <stdio.h>
#include <stdint.h>
#include <mmintrin.h>

uint8_t key(uint32_t m) {
  return 3 - (__builtin_clz(m|1) >> 3);
}

int main() {
  uint8_t m1 = key(10);
  uint8_t m2 = key(128);
  uint8_t m3 = key(256);
  uint8_t m4 = key(1025);

  printf ( "%u\n", (m4 << 6) | (m3 << 4) | (m2 << 2) | m1 );

  __m64 k = _mm_cvtsi32_si64(10);

  int m = _mm_cvtsi64_si32(k);
  printf( "after converting back to integer %d\n", m );
  
}

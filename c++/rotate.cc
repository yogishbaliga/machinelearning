#include <xmmintrin.h>
#include <stdint.h>
#include <stdio.h>

void rotate(const uint32_t *in, uint32_t *out) {


  __m128i a_ = _mm_loadu_si128((__m128i *) in);
  a_ = _mm_shuffle_epi32(a_, _MM_SHUFFLE(0, 3, 2, 1));
  _mm_storeu_si128((__m128i *) out, a_);
}

int main() {
  uint32_t o[] = {0, 1, 2, 3};
  rotate(o, o);
  printf( "%u %u %u %u\n", o[0], o[1], o[2], o[3] );
  rotate(o, o);
  printf( "%u %u %u %u\n", o[0], o[1], o[2], o[3] );
  rotate(o, o);
  printf( "%u %u %u %u\n", o[0], o[1], o[2], o[3] );
  rotate(o, o);
  printf( "%u %u %u %u\n", o[0], o[1], o[2], o[3] );
}

#include <emmintrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <stdint.h>
#include <stdio.h>

void print_arru8(const uint8_t *arr, size_t n) {
  for (int i = 0; i < n; ++i) {
    printf ( "%u ", arr[i] );
  }

  printf ("\n" );
}

void print_arri8(const int8_t *arr, size_t n) {
  for (int i = 0; i < n; ++i) {
    printf ( "%d ", arr[i] );
  }

  printf ("\n" );
}

void print_arru64(const uint64_t *arr, size_t n) {
  for (int i = 0; i < n; ++i) {
    printf ( "%llu ", arr[i] );
  }

  printf ("\n" );
}

void print_epu8(const __m128i m) {
  uint8_t a[16];
  _mm_store_si128((__m128i *) a, m);

  for (int i = 0; i < 16; ++i) {
    printf( "%u ", a[i] );
  }

  printf ("\n" );
}

void print_epu32(const __m128i m) {
  uint32_t a[4];
  _mm_store_si128((__m128i *) a, m);

  for (int i = 0; i < 4; ++i) {
    printf( "%u ", a[i] );
  }

  printf ("\n" );
}


void print_epu64(const __m128i m) {
  uint64_t a[2];
  _mm_store_si128((__m128i *) a, m);

  for (int i = 0; i < 2; ++i) {
    printf( "%llu ", a[i] );
  }

  printf ("\n" );
}

void print_ps(const __m128 m) {
  float a[4];
  _mm_store_ps(a, m);

  for (int i = 0; i < 4; ++i) {
    printf( "%.3f ", a[i] );
  }

  printf ("\n" );
}



int main() {
  
  {
  const uint8_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    /** loading 16 integers into XMM register. 
      *
      * _mm_load_si128 is used to load 16 8-bit integers, 8 16-bit integers, 4 32-bit integers or 2 64-bit integers
      */
    __m128i a_ = _mm_load_si128((__m128i *) arr);

    /** add 16 8-bit integers in parallel **/
    __m128i r_ = _mm_add_epi8(a_, a_);

    print_arru8(arr, 16);
    print_epu8(r_);
  }

  {
    printf( "multiplying 4 32-bit integers\n" );
    /** load 4 32-bit integers **/
    const uint32_t arr[] = {100, 200, 300, 400};
    __m128i a_ = _mm_load_si128((__m128i *) arr);
    __m128i r_ = _mm_add_epi32(a_, a_);

    print_epu32(r_);

    printf( "extracting 3rd value 32-bit values\n" );
    /** 2nd parameter is 0-based index. Should print 200 here **/
    uint32_t k = _mm_extract_epi32(r_, 2);
    printf( "3rd 32-bit value : %u\n", k );
 
  }

  {
    printf( "multiplying 2 64-bit integers\n" );
    /** load 2 64-bit integers **/
    const uint64_t arr[] = {100, 200};
    __m128i a_ = _mm_load_si128((__m128i *) arr);
    __m128i r_ = _mm_add_epi64(a_, a_);

    print_epu64(r_);

    printf( "extracting 2nd value 64-bit values\n" );
    /** 2nd parameter is 0-based index. Should print 200 here **/
    uint64_t k = _mm_extract_epi64(r_, 0);
    printf( "2nd 64-bit value : %llu\n", k );
  }

  {
    printf( "adding scalar values\n" );

    const float a[] = {4.0, 2.0, 3.0, 1.0};

    __m128 a_ = _mm_load_ps(a);
    __m128 r_ = _mm_add_ps(a_, a_);
    print_ps(r_);
  }

}

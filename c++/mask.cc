#include <emmintrin.h>
#include <memory.h>
#include <stdio.h>

static __m128i shuffle_mask[16];

int getBit(int value, int position) {
    return ( ( value & (1 << position) ) >> position);
}


void prepare_shuffling_dictionary() {

    for(int i = 0; i < 16; i++) {

        printf( "%d\n", i );
        int counter = 0;
        char permutation[16];
        memset(permutation, 0xFF, sizeof(permutation));
        for(char b = 0; b < 4; b++) {
            if(getBit(i, b)) {
                permutation[counter++] = 4*b;
                permutation[counter++] = 4*b + 1;
                permutation[counter++] = 4*b + 2;
                permutation[counter++] = 4*b + 3;
            }
        }

        printf( "i = %d => ", i );
        for (int m = 0; m < counter; ++m ) {
          printf( "%d, ", permutation[m] );
        }
        printf( "\n" );
        __m128i mask = _mm_loadu_si128((const __m128i*)permutation);
        shuffle_mask[i] = mask;
    }

    printf( "Returning\n" );
}

int main() {

  printf( "starting\n" );
  prepare_shuffling_dictionary();

  printf ("shuffling done\n");
  for (int i = 0; i < 16; ++i) {
    long long a[4];
    _mm_storeu_si128((__m128i *) &a, shuffle_mask[i]);
    printf( "mask : %llu %llu %llu %llu\n", a[0], a[1], a[2], a[3] );
  } 
}


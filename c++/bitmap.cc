#ifndef __bitmap_index_hh__
#define __bitmap_index_hh__

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <exception>
#include <algorithm>
#include <iostream>

using namespace std;

class BitMap {
  public:
    BitMap(const uint32_t max): 
          max_bits(max), bits(NULL), index(0) {
      bits = new uint32_t[max_bits];
    }

    bool set(const uint32_t b) {
      if (index >= max_bits) {
        return false;
      }

      bits[index++] = b;
      return true;
    }

    unsigned char * serialize() const {
      if (index == 0) return NULL;

      std::sort(bits, bits + index);
      uint32_t max = bits[index-1];

      uint32_t num_bits_per_bit = ceil(log2(max));

      uint32_t max_num_bytes = index * 4;

      // 25% less space, 

      return NULL;
    }

  private:
    uint32_t max_bits;
    uint32_t *bits;
    uint32_t index;
};

int main() {
  BitMap b(100);
  b.set(20);
  b.set(50);
  b.set(30);

  b.serialize();  
}

#endif

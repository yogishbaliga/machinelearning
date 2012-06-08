#include <stdint.h>
#include <immintrin.h>

void saxpy(float a, const float *x, const float *y, float * __restrict z) {
    size_t i = 0;
    __m256 a_ = _mm256_set1_ps(a);

    __m256 x1_ = _mm256_loadu_ps(x);
    __m256 y1_ = _mm256_loadu_ps(y);

    x1_ = _mm256_mul_ps(x1_, a_);
    x1_ = _mm256_add_ps(x1_, y1_);

    _mm256_storeu_ps(z, x1_);
}

int main() {
    float x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float z[8];
    saxpy(2.0, x, x, z);
}


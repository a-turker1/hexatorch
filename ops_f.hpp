#include <hexagon_types.h>

void add(float *__restrict__ left, float *__restrict__ right, float *__restrict__ output, int length);
void add(float *__restrict__ input, float scalar, float *__restrict__ output, int length);

static inline int32_t float_to_int(float scale)
{
    union
    {
        float f;
        int32_t i;
    } fp32 = {.f = scale};
    return fp32.i;
}

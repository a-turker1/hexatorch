
#include <stdio.h>
#include "ops.hpp"
#include "helper.hpp"

#define ARRAY_SIZE 256

int main()
{
    float *in1_vb = (float *)aligned_malloc(ARRAY_SIZE * sizeof(float), 128);
    float *in2_vb = (float *)aligned_malloc(ARRAY_SIZE * sizeof(float), 128);
    float *output = (float *)aligned_malloc(ARRAY_SIZE * sizeof(float), 128);
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        in1_vb[i] = 1.25f;
        in2_vb[i] = 1.21f;
    }
    add(in1_vb, in2_vb, output, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%f + %f = %f\n", in1_vb[i], in2_vb[i], output[i]);
    }
}
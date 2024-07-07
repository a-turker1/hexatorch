
#include <stdio.h>
#include "ops_f.hpp"
#include "helper.hpp"
#include <hexagon_types.h>
#include <hvx_hexagon_protos.h>

#define ARRAY_SIZE 32

int main()
{

    float *in1_vb = (float *)aligned_malloc(ARRAY_SIZE * sizeof(float), 1024);
    float *in2_vb = (float *)aligned_malloc(ARRAY_SIZE * sizeof(float), 1024);
    float *output = (float *)aligned_malloc(ARRAY_SIZE * sizeof(float), 1024);
    float scalar = 2.0;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        in1_vb[i] = i * 200.0 + 1.0;
        in2_vb[i] = 2.0;
    }

    mul(in1_vb, scalar, output, ARRAY_SIZE);

    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%f + %f = %f\n", in1_vb[i], in2_vb[i], output[i]);
    }

    return 0;
}
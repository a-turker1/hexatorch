
#include <stdio.h>
#include "ops.hpp"
#include "helper.hpp"
#include <hexagon_types.h>
#include <hvx_hexagon_protos.h>

#define ARRAY_SIZE 16

int main()
{

    int8_t *in1_vb = (int8_t *)aligned_malloc(ARRAY_SIZE * sizeof(int8_t), 1024);
    int8_t *in2_vb = (int8_t *)aligned_malloc(ARRAY_SIZE * sizeof(int8_t), 1024);
    int8_t *output = (int8_t *)aligned_malloc(ARRAY_SIZE * sizeof(int8_t), 1024);
    int8_t scalar = 5;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        in1_vb[i] = i + 1;
        in2_vb[i] = i + 1;
    }

    add(in1_vb, scalar, output, ARRAY_SIZE);

    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d\n", output[i]);
    }

    return 0;
}
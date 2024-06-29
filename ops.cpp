#include <stdlib.h>
#include <hexagon_types.h>

#define vmem(A) *((HVX_Vector *)(A))
#define vmemu(A) *((HVX_UVector *)(A))

void add(float *left, float *right, float *output, int length)
{
    HVX_Vector *hleft = (HVX_Vector *)left;
    HVX_Vector *hright = (HVX_Vector *)right;
    HVX_Vector *houtput = (HVX_Vector *)output;

    HVX_Vector out;

    int step = length / 32;
    for (size_t i = 0; i < step; i++)
    {

        out = Q6_Vqf32_vadd_VsfVsf(hleft[i], hright[i]);
        out = Q6_Vsf_equals_Vqf32(out);
        vmemu(houtput++) = out;
    }
}


#include <stdio.h>
#include <hexagon_protos.h>
#include <hvx_hexagon_protos.h>

#include "ops_f.hpp"
#include "helper.hpp"

#define vmem(A) *((HVX_Vector *)(A))
#define vmemu(A) *((HVX_UVector *)(A))

void add(float *__restrict__ left, float *__restrict__ right, float *__restrict__ output, int length)
{
    HVX_Vector *hleft = (HVX_Vector *)left;
    HVX_Vector *hright = (HVX_Vector *)right;
    HVX_Vector *houtput = (HVX_Vector *)output;

    int nstep = length / 32;
    int leftover = (length & 31) * sizeof(float);

    for (int i = 0; i < nstep; i++)
    {
        HVX_Vector out = Q6_Vqf32_vadd_VsfVsf(hleft[i], hright[i]);
        out = Q6_Vsf_equals_Vqf32(out);
        vmemu(&houtput[i]) = out;
    }

    if (leftover > 0)
    {

        HVX_VectorPred ql_not = Q6_Q_vsetq_R((size_t)(houtput + nstep));
        HVX_VectorPred qr = Q6_Q_vsetq2_R(leftover);
        ql_not = Q6_Q_or_QQn(ql_not, qr);

        HVX_Vector out = Q6_Vqf32_vadd_VsfVsf(hleft[nstep], hright[nstep]);
        out = Q6_Vsf_equals_Vqf32(out);
        Q6_vmem_QnRIV(ql_not, (HVX_Vector *)(houtput + nstep), out);
    }
}

void add(float *__restrict__ input, float scalar, float *__restrict__ output, int length)
{
    HVX_Vector *hinput = (HVX_Vector *)input;
    HVX_Vector *houtput = (HVX_Vector *)output;

    HVX_Vector scalar_vec = Q6_V_vsplat_R(float_to_int(scalar));

    int nstep = length / 32;
    int leftover = (length & 31) * sizeof(float);

    for (int i = 0; i < nstep; i++)
    {
        HVX_Vector out = Q6_Vqf32_vadd_VsfVsf(hinput[i], scalar_vec);
        out = Q6_Vsf_equals_Vqf32(out);
        vmemu(&houtput[i]) = out;
    }

    if (leftover > 0)
    {
        HVX_VectorPred ql_not = Q6_Q_vsetq_R((size_t)(houtput + nstep));
        HVX_VectorPred qr = Q6_Q_vsetq2_R(leftover);
        ql_not = Q6_Q_or_QQn(ql_not, qr);

        HVX_Vector out = Q6_Vqf32_vadd_VsfVsf(hinput[nstep], scalar_vec);
        out = Q6_Vsf_equals_Vqf32(out);
        Q6_vmem_QnRIV(ql_not, (HVX_Vector *)(houtput + nstep), out);
    }
}

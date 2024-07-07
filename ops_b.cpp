
#include <stdio.h>
#include "ops_b.hpp"
#include <hexagon_protos.h>
#include <hvx_hexagon_protos.h>

#define vmem(A) *((HVX_Vector *)(A))
#define vmemu(A) *((HVX_UVector *)(A))

void add(int8_t *__restrict__ left, int8_t *__restrict__ right, int8_t *__restrict__ output, int length)
{
    HVX_Vector *hleft = (HVX_Vector *)left;
    HVX_Vector *hright = (HVX_Vector *)right;
    HVX_Vector *houtput = (HVX_Vector *)output;

    int nstep = length / 128;
    int leftover = length & 127;
    for (int i = 0; i < nstep; i++)
    {
        HVX_Vector out = Q6_Vb_vadd_VbVb(hleft[i], hright[i]);
        vmemu(&houtput[i]) = out;
    }

    if (leftover > 0)
    {

        HVX_VectorPred ql_not = Q6_Q_vsetq_R((size_t)(houtput + nstep));
        HVX_VectorPred qr = Q6_Q_vsetq2_R(leftover);
        ql_not = Q6_Q_or_QQn(ql_not, qr);

        HVX_Vector out = Q6_Vb_vadd_VbVb(hleft[nstep], hright[nstep]);
        Q6_vmem_QnRIV(ql_not, (HVX_Vector *)(houtput + nstep), out);
    }
}

void add(int8_t *__restrict__ input, int8_t scalar, int8_t *__restrict__ output, int length)
{
    HVX_Vector *hinput = (HVX_Vector *)input;
    HVX_Vector *houtput = (HVX_Vector *)output;

    HVX_Vector scalar_vec = Q6_Vb_vsplat_R(scalar);

    int nstep = length / 128;
    int leftover = length & 127;

    for (int i = 0; i < nstep; i++)
    {
        HVX_Vector out = Q6_Vb_vadd_VbVb(hinput[i], scalar_vec);
        vmemu(&houtput[i]) = out;
    }

    if (leftover > 0)
    {
        HVX_VectorPred ql_not = Q6_Q_vsetq_R((size_t)(houtput + nstep));
        HVX_VectorPred qr = Q6_Q_vsetq2_R(leftover);
        ql_not = Q6_Q_or_QQn(ql_not, qr);

        HVX_Vector out = Q6_Vb_vadd_VbVb(hinput[nstep], scalar_vec);
        Q6_vmem_QnRIV(ql_not, (HVX_Vector *)(houtput + nstep), out);
    }
}

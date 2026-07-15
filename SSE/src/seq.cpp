#include "seq.h"

void seq()
{
    cout << "Sequential\n";
    seqAdd(gInt, "int");
    seqAdd(gFloat, "float");
    seqAdd(gDouble, "double");
}

void seq_mat()
{
    cout << "sequential Matrix Addition\n";
    seqMatAdd(gmInt, "int");
    seqMatAdd(gmFloat, "float");
    seqMatAdd(gmDouble, "double");

    cout << "Sequential Matrix Multiplication\n";
    seqMatMul(gmInt, "int");
    seqMatMul(gmFloat, "float");
    seqMatMul(gmDouble, "double");
}
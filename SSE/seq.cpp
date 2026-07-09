#include "seq.h"

void seq()
{
    cout << "Sequential\n";

    seqAdd(gInt, "int");

    seqAdd(gFloat, "float");

    seqAdd(gDouble, "double");
}
#include "main.h"

int main()
{
    //vectors add
    initVecs();

    seq();

    sse();

    verifyAll();

    //matrix add and mul

    initMats();

    seq_mat();

    sse_mat();

    return 0;
}
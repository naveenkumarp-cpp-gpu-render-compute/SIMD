#include "common.h"

Vecs<int> gInt;
Vecs<float> gFloat;
Vecs<double> gDouble;

void initVecs()
{
    initVec(gInt);
    initVec(gFloat);
    initVec(gDouble);
}
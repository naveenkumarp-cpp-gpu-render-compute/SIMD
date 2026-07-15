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

Vecs<int> gmInt;
Vecs<float> gmFloat;
Vecs<double> gmDouble;

void initMats()
{
    initMat(gmInt);
    initMat(gmFloat);
    initMat(gmDouble);
}
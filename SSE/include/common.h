#pragma once

#include "config.h"

template<typename T>
struct Vecs
{
    T* a = nullptr;
    T* b = nullptr;
    T* seq = nullptr;
    T* simd = nullptr;
};

extern Vecs<int> gInt;
extern Vecs<float> gFloat;
extern Vecs<double> gDouble;

template<typename T>
T* createVec(size_t size)
{
    return new T[size];
}

template<typename T>
void initVec(Vecs<T>& v)
{
    v.a = createVec<T>(VEC_SIZE);
    v.b = createVec<T>(VEC_SIZE);
    v.seq = createVec<T>(VEC_SIZE);
    v.simd = createVec<T>(VEC_SIZE);

    for (int i = 0;i < VEC_SIZE;i++)
    {
        v.a[i] = static_cast<T>(i);
        v.b[i] = static_cast<T>(i * 2);
    }
}

void initVecs();
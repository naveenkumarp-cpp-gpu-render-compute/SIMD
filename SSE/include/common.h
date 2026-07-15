#pragma once

#include "config.h"

template<typename T>
struct Vecs
{
    T* a = nullptr;
    T* b = nullptr;
    T* seq = nullptr;
    T* seq_mul = nullptr;
    T* simd = nullptr;
    T* simd_mul = nullptr;
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



extern Vecs<int> gmInt;
extern Vecs<float> gmFloat;
extern Vecs<double> gmDouble;

template<typename T>
void initMat(Vecs<T>& v){
    v.a = createVec<T>(MATA_ROWS * MATA_COLS);
    v.b = createVec<T>(MATB_ROWS * MATB_COLS);
    v.seq = createVec<T>(MATA_ROWS * MATB_COLS);
    v.simd = createVec<T>(MATA_ROWS * MATB_COLS);


    v.seq_mul = createVec<T>(MATA_ROWS * MATB_COLS);
    v.simd_mul = createVec<T>(MATA_ROWS * MATB_COLS);

    for (int i = 0;i < MATA_ROWS * MATA_COLS;i++)
    {
        v.a[i] = static_cast<T>(i);
        v.b[i] = static_cast<T>(i * 2);
    }
}


void initMats();
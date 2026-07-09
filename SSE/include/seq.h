#pragma once

#include "common.h"

void seq();

template<typename T>
void seqAdd(Vecs<T>& v, const char* name)
{
    timer t;

    t.start = high_resolution_clock::now();

    for (int i = 0;i < VEC_SIZE;i++)
        v.seq[i] = v.a[i] + v.b[i];

    t.end = high_resolution_clock::now();

    cout
        << left
        << setw(10)
        << name
        << t.measure_time_ms()
        << " ms"
        << endl;
}
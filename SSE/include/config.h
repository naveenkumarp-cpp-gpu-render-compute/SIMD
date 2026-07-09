#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using chrono::high_resolution_clock;

#define VEC_SIZE 10000000

struct timer
{
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;

    double measure_time_ms()
    {
        return chrono::duration<double, milli>(end - start).count();
    }
};
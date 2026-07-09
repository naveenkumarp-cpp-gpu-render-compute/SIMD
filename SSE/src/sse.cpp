#include "sse.h"



void sseAddInt(Vecs<int>& v)
{
    timer t;

    t.start = high_resolution_clock::now();

    int i = 0;

    // Process 4 integers at a time
    for (; i <= VEC_SIZE - 4; i += 4)
    {
        // Load
        __m128i a = _mm_loadu_si128((__m128i*) & v.a[i]);
        __m128i b = _mm_loadu_si128((__m128i*) & v.b[i]);

        // Compute
        __m128i c = _mm_add_epi32(a, b);

        // Store
        _mm_storeu_si128((__m128i*) & v.simd[i], c);
    }

    // Remaining elements
    for (; i < VEC_SIZE; i++)
        v.simd[i] = v.a[i] + v.b[i];

    t.end = high_resolution_clock::now();

    cout << left
        << setw(10) << "int"
        << t.measure_time_ms()
        << " ms" << endl;
}

void sseAddFloat(Vecs<float>& v)
{
    timer t;

    t.start = high_resolution_clock::now();

    int i = 0;

    // Process 4 floats at a time
    for (; i <= VEC_SIZE - 4; i += 4)
    {
        // Load
        __m128 a = _mm_loadu_ps(&v.a[i]);
        __m128 b = _mm_loadu_ps(&v.b[i]);

        // Compute
        __m128 c = _mm_add_ps(a, b);

        // Store
        _mm_storeu_ps(&v.simd[i], c);
    }

    // Remaining elements
    for (; i < VEC_SIZE; i++)
        v.simd[i] = v.a[i] + v.b[i];

    t.end = high_resolution_clock::now();

    cout << left
        << setw(10) << "float"
        << t.measure_time_ms()
        << " ms" << endl;
}


void sseAddDouble(Vecs<double>& v)
{
    timer t;

    t.start = high_resolution_clock::now();

    int i = 0;

    // Process 2 doubles at a time
    for (; i <= VEC_SIZE - 2; i += 2)
    {
        // Load
        __m128d a = _mm_loadu_pd(&v.a[i]);
        __m128d b = _mm_loadu_pd(&v.b[i]);

        // Compute
        __m128d c = _mm_add_pd(a, b);

        // Store
        _mm_storeu_pd(&v.simd[i], c);
    }

    // Remaining elements
    for (; i < VEC_SIZE; i++)
        v.simd[i] = v.a[i] + v.b[i];

    t.end = high_resolution_clock::now();

    cout << left
        << setw(10) << "double"
        << t.measure_time_ms()
        << " ms" << endl;
}

void sse()
{
	cout << "SSE\n";
    sseAddInt(gInt);
    sseAddFloat(gFloat);
    sseAddDouble(gDouble);
}
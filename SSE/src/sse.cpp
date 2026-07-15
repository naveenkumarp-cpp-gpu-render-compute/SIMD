#include "sse.h"

void sseAddInt(Vecs<int> &v)
{
    timer t;

    t.start = high_resolution_clock::now();

    int i = 0;

    // Process 4 integers at a time
    for (; i <= VEC_SIZE - 4; i += 4)
    {
        // Load
        __m128i a = _mm_loadu_si128((__m128i *)&v.a[i]);
        __m128i b = _mm_loadu_si128((__m128i *)&v.b[i]);

        // Compute
        __m128i c = _mm_add_epi32(a, b);

        // Store
        _mm_storeu_si128((__m128i *)&v.simd[i], c);
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

void sseAddFloat(Vecs<float> &v)
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

void sseAddDouble(Vecs<double> &v)
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

void sseMatAdd(Vecs<int> &v, const char *name)
{
    timer t;

    t.start = high_resolution_clock::now();
    int i, j;
    for (i = 0; i < MATA_ROWS; i++)
    {
        for (j = 0; j <= MATA_COLS - 4; j += 4)
        {
            __m128i a = _mm_loadu_si128((__m128i *)&v.a[i * MATA_COLS + j]);
            __m128i b = _mm_loadu_si128((__m128i *)&v.b[i * MATA_COLS + j]);
            __m128i c = _mm_add_epi32(a, b);
            _mm_storeu_si128((__m128i *)&v.simd[i * MATA_COLS + j], c);
        }
    }
    // Handle remaining elements
    for (; j < MATA_COLS; j++)
    {
        v.simd[i * MATA_COLS + j] = v.a[i * MATA_COLS + j] + v.b[i * MATA_COLS + j];
    }

    t.end = high_resolution_clock::now();

    cout << left
         << setw(10) << name
         << t.measure_time_ms()
         << " ms" << endl;
}

void sseMatAdd(Vecs<float> &v, const char *name)
{
    timer t;

    t.start = high_resolution_clock::now();

    int i, j;
    for (i = 0; i < MATA_ROWS; i++)
    {
        for (j = 0; j <= MATA_COLS - 4; j += 4)
        {
            __m128 a = _mm_loadu_ps(&v.a[i * MATA_COLS + j]);
            __m128 b = _mm_loadu_ps(&v.b[i * MATA_COLS + j]);
            __m128 c = _mm_add_ps(a, b);
            _mm_storeu_ps(&v.simd[i * MATA_COLS + j], c);
        }
    }
    // Handle remaining elements
    for (; j < MATA_COLS; j++)
    {
        v.simd[i * MATA_COLS + j] = v.a[i * MATA_COLS + j] + v.b[i * MATA_COLS + j];
    }

    t.end = high_resolution_clock::now();

    cout << left
         << setw(10) << name
         << t.measure_time_ms()
         << " ms" << endl;
}

void sseMatAdd(Vecs<double> &v, const char *name)
{
    timer t;

    t.start = high_resolution_clock::now();

    int i, j;
    for (i = 0; i < MATA_ROWS; i++)
    {
        for (j = 0; j <= MATA_COLS - 2; j += 2)
        {
            __m128d a = _mm_loadu_pd(&v.a[i * MATA_COLS + j]);
            __m128d b = _mm_loadu_pd(&v.b[i * MATA_COLS + j]);
            __m128d c = _mm_add_pd(a, b);
            _mm_storeu_pd(&v.simd[i * MATA_COLS + j], c);
        }
    }
    // Handle remaining elements
    for (; j < MATA_COLS; j++)
    {
        v.simd[i * MATA_COLS + j] = v.a[i * MATA_COLS + j] + v.b[i * MATA_COLS + j];
    }

    t.end = high_resolution_clock::now();

    cout << left
         << setw(10) << name
         << t.measure_time_ms()
         << " ms" << endl;
}
void sseMatMul(Vecs<int> &v, const char *name)
{
    if (MATA_COLS != MATB_ROWS)
    {
        cout << "Matrix multiplication not possible due to incompatible dimensions\n";
        return;
    }

    timer t;
    t.start = high_resolution_clock::now();

    for (int i = 0; i < MATA_ROWS; i++)
    {
        for (int j = 0; j < MATB_COLS; j++)
        {
            __m128i vsum = _mm_setzero_si128();

            int k = 0;
            for (; k <= MATA_COLS - 4; k += 4)
            {
                __m128i a = _mm_loadu_si128((__m128i *)&v.a[i * MATA_COLS + k]);

                __m128i b = _mm_set_epi32(
                    v.b[(k + 3) * MATB_COLS + j],
                    v.b[(k + 2) * MATB_COLS + j],
                    v.b[(k + 1) * MATB_COLS + j],
                    v.b[(k + 0) * MATB_COLS + j]);

                vsum = _mm_add_epi32(vsum, _mm_mullo_epi32(a, b));
            }

            alignas(16) int temp[4];
            _mm_store_si128((__m128i *)temp, vsum);

            int sum = temp[0] + temp[1] + temp[2] + temp[3];

            for (; k < MATA_COLS; k++)
                sum += v.a[i * MATA_COLS + k] * v.b[k * MATB_COLS + j];

            v.simd_mul[i * MATB_COLS + j] = sum;
        }
    }

    t.end = high_resolution_clock::now();

    cout << left << setw(10) << name
         << t.measure_time_ms() << " ms\n";
}

void sseMatMul(Vecs<float> &v, const char *name)
{
    if (MATA_COLS != MATB_ROWS)
    {
        cout << "Matrix multiplication not possible due to incompatible dimensions\n";
        return;
    }

    timer t;
    t.start = high_resolution_clock::now();

    for (int i = 0; i < MATA_ROWS; i++)
    {
        for (int j = 0; j < MATB_COLS; j++)
        {
            __m128 vsum = _mm_setzero_ps();

            int k = 0;
            for (; k <= MATA_COLS - 4; k += 4)
            {
                __m128 a = _mm_loadu_ps(&v.a[i * MATA_COLS + k]);

                __m128 b = _mm_set_ps(
                    v.b[(k + 3) * MATB_COLS + j],
                    v.b[(k + 2) * MATB_COLS + j],
                    v.b[(k + 1) * MATB_COLS + j],
                    v.b[(k + 0) * MATB_COLS + j]);

                vsum = _mm_add_ps(vsum, _mm_mul_ps(a, b));
            }

            alignas(16) float temp[4];
            _mm_store_ps(temp, vsum);

            float sum = temp[0] + temp[1] + temp[2] + temp[3];

            for (; k < MATA_COLS; k++)
                sum += v.a[i * MATA_COLS + k] * v.b[k * MATB_COLS + j];

            v.simd_mul[i * MATB_COLS + j] = sum;
        }
    }

    t.end = high_resolution_clock::now();

    cout << left << setw(10) << name
         << t.measure_time_ms() << " ms\n";
}

void sseMatMul(Vecs<double> &v, const char *name)
{
    if (MATA_COLS != MATB_ROWS)
    {
        cout << "Matrix multiplication not possible due to incompatible dimensions\n";
        return;
    }

    timer t;
    t.start = high_resolution_clock::now();

    for (int i = 0; i < MATA_ROWS; i++)
    {
        for (int j = 0; j < MATB_COLS; j++)
        {
            __m128d vsum = _mm_setzero_pd();

            int k = 0;
            for (; k <= MATA_COLS - 2; k += 2)
            {
                __m128d a = _mm_loadu_pd(&v.a[i * MATA_COLS + k]);

                __m128d b = _mm_set_pd(
                    v.b[(k + 1) * MATB_COLS + j],
                    v.b[(k + 0) * MATB_COLS + j]);

                vsum = _mm_add_pd(vsum, _mm_mul_pd(a, b));
            }

            alignas(16) double temp[2];
            _mm_store_pd(temp, vsum);

            double sum = temp[0] + temp[1];

            for (; k < MATA_COLS; k++)
                sum += v.a[i * MATA_COLS + k] * v.b[k * MATB_COLS + j];

            v.simd_mul[i * MATB_COLS + j] = sum;
        }
    }

    t.end = high_resolution_clock::now();

    cout << left << setw(10) << name
         << t.measure_time_ms() << " ms\n";
}

void sse_mat()
{
    cout << "SSE Matrix Addition\n";
    sseMatAdd(gmInt, "int");
    sseMatAdd(gmFloat, "float");
    sseMatAdd(gmDouble, "double");

    verifyAllMat();

    cout << "SSE Matrix Multiplication\n";
    sseMatMul(gmInt, "int");
    sseMatMul(gmFloat, "float");
    sseMatMul(gmDouble, "double");

    verifyAllMat(true);
}
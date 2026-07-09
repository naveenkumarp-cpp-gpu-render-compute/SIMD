#include "verify.h"
#include <cmath>

template<typename T>
bool verify(const Vecs<T>& v)
{
    for (int i = 0; i < VEC_SIZE; i++)
    {
        if (v.seq[i] != v.simd[i])
        {
            cout << "Mismatch at index " << i << endl;
            return false;
        }
    }
    return true;
}

// float specialization
template<>
bool verify<float>(const Vecs<float>& v)
{
    const float eps = 1e-6f;

    for (int i = 0; i < VEC_SIZE; i++)
    {
        if (fabs(v.seq[i] - v.simd[i]) > eps)
        {
            cout << "Mismatch at index " << i << endl;
            return false;
        }
    }
    return true;
}

// double specialization
template<>
bool verify<double>(const Vecs<double>& v)
{
    const double eps = 1e-12;

    for (int i = 0; i < VEC_SIZE; i++)
    {
        if (fabs(v.seq[i] - v.simd[i]) > eps)
        {
            cout << "Mismatch at index " << i << endl;
            return false;
        }
    }
    return true;
}

void verifyAll()
{
    cout << "\nVerification\n";

    cout << "int    : " << (verify(gInt) ? "PASS" : "FAIL") << endl;
    cout << "float  : " << (verify(gFloat) ? "PASS" : "FAIL") << endl;
    cout << "double : " << (verify(gDouble) ? "PASS" : "FAIL") << endl;
}
#include "verify.h"
#include <cmath>

template <typename T>
bool verify(const Vecs<T> &v)
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

template <typename T>
bool verifyMat(const Vecs<T> &v)
{
    for (int i = 0; i < MATA_ROWS * MATA_COLS; i++)
    {
        if (v.seq[i] != v.simd[i])
        {
            cout << "Mismatch at index " << i << endl;
            return false;
        }
    }
    return true;
}

template <typename T>
bool verifyMatmul(const Vecs<T> &v)
{
    for (int i = 0; i < MATA_ROWS * MATB_COLS; i++)
    {

        T diff = fabs(v.seq_mul[i] - v.simd_mul[i]);
        T limit = fabs(v.seq_mul[i]) * 1e-5;

        if (diff > limit)
        {
            cout << "Mismatch at index " << i << endl;
            std::cout << std::setprecision(20)
                      << "seq  = " << v.seq_mul[i] << '\n'
                      << "simd = " << v.simd_mul[i] << '\n';
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

void verifyAllMat(bool mat)
{
    if (!mat)
    {
        cout << "\nMatrix add Verification\n";

        cout << "int    : " << (verifyMat(gmInt) ? "PASS" : "FAIL") << endl;
        cout << "float  : " << (verifyMat(gmFloat) ? "PASS" : "FAIL") << endl;
        cout << "double : " << (verifyMat(gmDouble) ? "PASS" : "FAIL") << endl;
    }
    else
    {
        cout << "\nMatrix mul Verification\n";

        cout << "int    : " << (verifyMatmul(gmInt) ? "PASS" : "FAIL") << endl;
        cout << "float  : " << (verifyMatmul(gmFloat) ? "PASS" : "FAIL") << endl;
        cout << "double : " << (verifyMatmul(gmDouble) ? "PASS" : "FAIL") << endl;
    }
}
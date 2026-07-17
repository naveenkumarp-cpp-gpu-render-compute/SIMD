#pragma once

#include "common.h"

void seq();
void seq_mat();

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

template<typename T>
void seqMatAdd(Vecs<T>& v, const char* name){

    if(MATA_ROWS != MATB_ROWS || MATA_COLS != MATB_COLS){
        cout << "Matrix addition not possible due to incompatible dimensions" << endl;
        return;
    }

    timer t;

    t.start = high_resolution_clock::now();

    for (int i = 0;i < MATA_ROWS;i++)
    {
        for (int j = 0;j < MATA_COLS;j++)
        {
            v.seq[i * MATA_COLS + j] = v.a[i * MATA_COLS + j] + v.b[i * MATA_COLS + j];
        }
    }

    t.end = high_resolution_clock::now();

    cout
        << left
        << setw(10)
        << name
        << t.measure_time_ms()
        << " ms"
        << endl;
}


template<typename T>
void seqMatMul(Vecs<T>& v, const char* name){   

    if(MATA_COLS != MATB_ROWS){
        cout << "Matrix multiplication not possible due to incompatible dimensions" << endl;
        return;
    }

    timer t;

    t.start = high_resolution_clock::now();


    for( int i = 0; i < MATA_ROWS; i++)
    {
        for( int j = 0; j < MATB_COLS; j++)
        {
            v.seq_mul[ i * MATB_COLS + j ] = 0;
            for( int k = 0; k < MATB_ROWS; k++)
            {
                v.seq_mul[ i * MATB_COLS + j ] += v.a[i*MATA_COLS + k ] * v.b[k*MATB_COLS + j];
            }
        }
    }

    t.end = high_resolution_clock::now();

    cout
        << left
        << setw(10)
        << name
        << t.measure_time_ms()
        << " ms"
        << endl;   
}
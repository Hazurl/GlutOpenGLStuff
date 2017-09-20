#pragma once

#include <initializer_list>
#include <iostream>

namespace glhaz {

template<typename T, unsigned int R = 4, unsigned C = R>
class Mat {
public:
    Mat(std::initializer_list<T> l) : data(l) {

    }

    Mat(T default_value = 0) : data{ default_value } {

    }

    ~Mat() {

    }

    operator float* () {
        return data;
    }

    class const_bracket_helper {
    private:
        const T (*data)[R][C];
        const unsigned int r;
    public:
        const_bracket_helper(const T(*data)[R][C], unsigned int r) : data(data), r(r) {}
        const T& operator [] (unsigned int c) const {
            return (*data)[r][c];
        }
    };
    class bracket_helper {
    private:
        T (*data)[R][C];
        unsigned int r;
    public:
        bracket_helper(T(*data)[R][C], unsigned int r) : data(data), r(r) {}
        T& operator [] (unsigned int c) {
            return (*data)[r][c];
        }
    };
    
    const const_bracket_helper operator [] (unsigned int idx) const {
        return const_bracket_helper(&data, idx);
    }
    bracket_helper operator [] (unsigned int idx) {
        return bracket_helper(&data, idx);
    }

    T& at(unsigned int r, unsigned int c) {
        return data[r][c];
    }

    Mat<T, R, C>& operator += (Mat<T, R, C> const& m) {
        for (unsigned int r = 0; r < R; r++)
            for(unsigned int c = 0; c < C; c++)
                data[r][c] += m[r][c]; 
    }

    template<unsigned int N>
    Mat<T, R, C>& operator *= (Mat<T, C, N> const& m) {
        T res[R][C];
        for (unsigned int r = 0; r < R; ++r)
            for(unsigned int n = 0; n < N; ++n)
                for(unsigned int k = 0; k < C; ++k)
                    res[r][n] += data[r][k] * m[k][n];
        data = res;
    }

    template<unsigned int N>
    Mat<T, R, C> operator * (Mat<T, C, N> const& m) {
        Mat<T, R, C> res;
        for (unsigned int r = 0; r < R; ++r)
            for(unsigned int n = 0; n < N; ++n)
                for(unsigned int k = 0; k < C; ++k)
                    res[r][n] += data[r][k] * m[k][n];
        return res;
    }

    Mat<T, R, C>& operator *= (T const& a) {
        for (unsigned int r = 0; r < R; r++)
            for(unsigned int c = 0; c < C; c++)
                data[r][c] *= a; 
    }

private:
    T data[R][C];
};

template<typename T, unsigned int R, unsigned int C>
void mat_to_console(Mat<T, R, C> const& m) {
    for(unsigned int i = 0; i<4; ++i) {
        for(unsigned int j = 0; j < 4; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T, unsigned int S> 
Mat<T, S, S> matIdentity(T default_value = 1) {
    Mat<T, S, S> m;
    for(unsigned int s = 0; s < S; ++s)
        m[s][s] = default_value;
    return m;
}

template<unsigned int R, unsigned C = R>
using Matf = Mat<float, R, C>;

template<unsigned int R, unsigned C = R>
using Mati = Mat<int, R, C>;

template<unsigned int R, unsigned C = R>
using Matui = Mat<unsigned int, R, C>;

template<unsigned int R, unsigned C = R>
using Matd = Mat<double, R, C>;

using Mat4f = Matf<4>;
using Mat4i = Mati<4>;
using Mat4ui = Matui<4>;
using Mat4d = Matd<4>;

}
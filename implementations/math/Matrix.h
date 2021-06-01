/**
 * Description: Matrix class that supports matrix operations.
 * Source: own
 * Verification: https://www.hackerearth.com/problem/algorithm/pk-and-interesting-language/description/
 * Time: fast
 */

template<typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> mat;

    Matrix(int _n, int _m) : n(_n), m(_m), mat(n, vector<T>(m)) {}

    Matrix(const vector<vector<T>> &_mat) : n((int) _mat.size()), m((int) _mat[0].size()), mat(_mat) {}

    Matrix& operator += (const Matrix &other) {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                mat[i][j] += other.mat[i][j];
        return *this;
    }

    Matrix& operator -= (const Matrix &other) {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                mat[i][j] -= other.mat[i][j];
        return *this;
    }

    Matrix operator * (const Matrix &other) const {
        Matrix ret(n, other.m);
        for (int i=0; i<n; i++)
            for (int k=0; k<m; k++)
                for (int j=0; j<other.m; j++)
                    ret.mat[i][j] += mat[i][k] * other.mat[k][j];
        return ret;
    }

    friend Matrix operator + (Matrix a, const Matrix &b) {
        return a += b;
    }

    friend Matrix operator - (Matrix a, const Matrix &b) {
        return a -= b;
    }

    Matrix& operator *= (const Matrix &other) {
        return *this = *this * other;
    }

    vector<T>& operator [] (int i) {
        return mat[i];
    }

    friend Matrix power(Matrix a, long long b) {
        Matrix ret(a.n, a.m);
        for (int i=0; i<a.n; i++)
            ret[i][i] = 1;
        while (b > 0) {
            if (b & 1)
                ret *= a;
            a *= a;
            b >>= 1;
        }
        return ret;
    }

    friend ostream& operator << (ostream &os, const Matrix &a) {
        return os << a.mat;
    }
};

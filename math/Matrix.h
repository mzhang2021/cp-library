/**
 * Description: Matrix class that supports matrix operations.
 * Source: own
 * Verification: https://www.hackerearth.com/problem/algorithm/pk-and-interesting-language/description/
 * Time: fast
 */

template<int MOD>
struct Matrix {
    int n, m;
    vector<vector<long long>> mat;

    Matrix(int _n, int _m) : n(_n), m(_m), mat(n, vector<long long>(m)) {}

    Matrix operator += (const Matrix &other) {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++) {
                mat[i][j] += other.mat[i][j];
                if (mat[i][j] >= MOD) mat[i][j] -= MOD;
            }
        return *this;
    }

    Matrix operator -= (const Matrix &other) {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++) {
                mat[i][j] -= other.mat[i][j];
                if (mat[i][j] < 0) mat[i][j] += MOD;
            }
        return *this;
    }

    Matrix operator * (const Matrix &other) const {
        Matrix ret(n, other.m);
        for (int i=0; i<n; i++)
            for (int k=0; k<m; k++)
                for (int j=0; j<other.m; j++) {
                    ret.mat[i][j] += mat[i][k] * other.mat[k][j] % MOD;
                    if (ret.mat[i][j] >= MOD)
                        ret.mat[i][j] -= MOD;
                }
        return ret;
    }

    friend Matrix operator + (Matrix a, const Matrix &b) {
        return a += b;
    }

    friend Matrix operator - (Matrix a, const Matrix &b) {
        return a -= b;
    }

    Matrix operator *= (const Matrix &other) {
        return *this = *this * other;
    }

    vector<long long>& operator [] (int i) {
        return mat[i];
    }

    friend Matrix power(Matrix m, long long b) {
        Matrix ret(m.n, m.m);
        for (int i=0; i<m.n; i++)
            ret[i][i] = 1;
        while (b > 0) {
            if (b & 1)
                ret *= m;
            m *= m;
            b >>= 1;
        }
        return ret;
    }
};

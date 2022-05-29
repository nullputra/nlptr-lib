template <class T>
struct SquareMatrix {
   private:
    int _n;
    T **mat;

   public:
    SquareMatrix() {}
    SquareMatrix(int n) : _n(n) {
        mat = new T *[_n];
        for (int i = 0; i < _n; i++) {
            mat[i] = new T[_n];
            for (int j = 0; j < _n; j++) mat[i][j] = 0;
        }
    }
    T &operator()(int i, int j) const {
        assert(0 <= i && i < _n && 0 <= j && j < _n);
        return mat[i][j];
    }
    SquareMatrix &operator*=(const SquareMatrix &a) {
        SquareMatrix mul(_n);
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < a._n; j++) {
                for (int k = 0; k < _n; k++) mul(i, j) = (mul(i, j) + mat[i][k] * a(k, j));
            }
        }
        swap(mat, mul.mat);
        return *this;
    }
    SquareMatrix operator*(const SquareMatrix &a) const { return SquareMatrix(*this) *= a; }
    static SquareMatrix id_mat(int m) {
        SquareMatrix id(m);
        for (int i = 0; i < m; i++) id(i, i) = 1;
        return id;
    }
    SquareMatrix pow(long long x) {
        SquareMatrix a(*this), res(SquareMatrix::id_mat(_n));
        while (x) {
            if (x & 1) res *= a;
            a *= a, x /= 2;
        }
        return res;
    }
    void print() {
#ifdef _DEBUG
        for (int i = 0; i < _n; i++) {
            cout << '[';
            for (int j = 0; j < _n; j++) {
                if (j) cout << ", ";
                cout << (*this)(i, j).val();
            }
            cout << "]\n";
        }
#endif
    }
};

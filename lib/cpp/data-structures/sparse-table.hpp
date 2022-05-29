template <class T>
struct SparseTable {
    int n, logn;
    vector<vector<T>> _v;
    using F = function<T(T, T)>;
    F _f;
    SparseTable(vector<T> &v, const F &f)
        : n(v.size()), logn(log2(n) + 1), _v(logn), _f(f) {
        _v[0].resize(n);
        for (int j = 0; j < n; j++) _v[0][j] = v[j];
        for (int i = 1; i < logn; i++) {
            int i_max = n + 1 - (1 << i);
            _v[i].resize(i_max);
            for (int j = 0; j < i_max; j++) {
                _v[i][j] = _f(_v[i - 1][j], _v[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T get(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int i = log2(r - l);
        return _f(_v[i][l], _v[i][r - (1 << i)]);
    }
    void print() {
#ifdef _DEBUG
        for (int i = 0; i < logn; i++) {
            for (int j = 0; j < (n + 1 - (1 << i)); j++) {
                string sj = to_string(j);
                if (sj.size() == 1) sj = ' ' + sj;
                cout << "_v[" << i << "][" << sj << "] = _f[" << sj << "," << sj << " + 1<<" << i << ") = " << _v[i][j] << '\n';
            }
        }
#endif
    }
};

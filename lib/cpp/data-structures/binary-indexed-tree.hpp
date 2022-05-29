template <class T>
struct BinaryIndexedTree {
   private:
    int _n;
    vector<vector<T>> v;
    bool uses_raq = false;

   public:
    BinaryIndexedTree(int n) : _n(n + 1), v(2, vector<T>(_n)) {}
    void add(T x, int l, int r = -1) {
        if (r == -1) {
            assert(1 <= l && l <= _n);
            _add(false, l, x);
            return;
        }
        uses_raq = true;
        assert(1 <= l && l <= r && r <= _n);
        _add(false, l, -x * (l - 1));
        _add(false, r, x * (r - 1));
        _add(true, l, x);
        _add(true, r, -x);
    }
    T sum(int i) {
        assert(1 <= i && i <= _n);
        if (--i == 0) return 0;
        return uses_raq ? _sum(false, i) + _sum(true, i) * i : _sum(false, i);
    }
    T range_sum(int l, int r) {
        assert(1 <= l && l <= _n && 1 <= r && r <= _n);
        return sum(r) - sum(l);
    }
    T operator[](int i) {
        assert(1 <= i && i <= _n);
        return range_sum(i, i + 1);
    }
    void print() {
#ifdef _DEBUG
        for (int i = 1; i < _n; i++) cout << (*this)[i] << ' ';
        cout << '\n';
#endif
    }

   private:
    void _add(bool is_raq, int i, T x) {
        for (; i < _n; i += i & -i) v[is_raq][i] += x;
    }
    T _sum(bool is_raq, int i) {
        T tot = 0;
        for (; i > 0; i -= i & -i) tot += v[is_raq][i];
        return tot;
    }
};

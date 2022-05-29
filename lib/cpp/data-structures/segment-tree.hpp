template <class V, class T>
struct SegmentTree {
   private:
    int n0, n, logn;
    vector<V> _vals;
    V _ev;
    using FV = function<V(V &, V &)>;
    FV &_fv;
    vector<T> tag;
    T _et;
    using FT = function<T(T &, T &)>;
    FT &_ft;
    using FM = function<V(T &, V &)>;
    FM &_fm;

   public:
    SegmentTree(vector<V> &vals, V &ev, FV fv, T &et, FT ft, FM fm)
        : n0(vals.size()), _ev(ev), _fv(fv), _et(et), _ft(ft), _fm(fm) {
        logn = 31 - __builtin_clz(2 * n0 - 1);
        n = 1 << logn;
        init(vals);
    }
    void init(vector<V> &vals) {
        assert(n0 == (int)vals.size());
        _vals = vector<V>(n * 2, _ev), tag = vector<T>(n, _et);
        copy(vals.begin(), vals.end(), _vals.begin() + n);
        for (int k = n - 1; k > 0; k--) fv_val(k);
    }
    void apply(T t, int l, int r = -1) {
        if (r == -1) {
            assert(0 <= l && l < n0);
            eval(l += n);
            add_tag(l, t);
            for (int k = 1; k <= logn; k++) fv_val(l >> k);
            return;
        }
        assert(0 <= l && l <= r && r <= n0);
        if (l == r) return;
        eval(l += n, r += n);
        for (int L = l, R = r; L < R; L >>= 1, R >>= 1) {
            if (L & 1) add_tag(L++, t);
            if (R & 1) add_tag(--R, t);
        }
        for (int k = 1; k <= logn; k++) {
            if ((l >> k << k) != l) fv_val(l >> k);
            if ((r >> k << k) != r) fv_val((r - 1) >> k);
        }
    }
    template <class F>
    int leftmost(int l, F &f) {
        assert(0 <= l && l <= n0);
        if (l == n0) return n0 + 1;
        l += n;
        eval(l);
        V cur = _ev;
        do {
            l >>= __builtin_ctz(l);
            if (f(_fv(cur, _vals[l]))) {
                while (l < n) {
                    push_tag(l);
                    l <<= 1;
                    if (V tmp = _fv(cur, _vals[l]); !f(tmp)) cur = tmp, l++;
                }
                return l - n + 1;
            }
            cur = _fv(cur, _vals[l++]);
        } while ((l & -l) != l);
        return n0 + 1;
    }
    template <class F>
    int rightmost(int r, F &f) {
        assert(0 <= r && r <= n0);
        if (r == 0) return -1;
        r += n;
        eval(r - 1);
        V cur = _ev;
        do {
            r >>= __builtin_ctz(r);
            if (r) r--;
            if (f(_fv(_vals[r], cur))) {
                while (r < n) {
                    push_tag(r);
                    r = r * 2 + 1;
                    if (V tmp = _fv(_vals[r], cur); !f(tmp)) cur = tmp, r--;
                }
                return r - n;
            }
            cur = _fv(_vals[r], cur);
        } while ((r & -r) != r);
        return -1;
    }
    V prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n0);
        if (l == r) return _ev;
        eval(l += n, r += n);
        V L = _ev, R = _ev;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = _fv(L, _vals[l++]);
            if (r & 1) R = _fv(_vals[--r], R);
        }
        return _fv(L, R);
    }
    V operator[](int i) {
        assert(0 <= i && i <= n0);
        eval(i += n);
        return _vals[i];
    }
    void print() {
        cout << "seg: [";
        for (int i = 0; i < n0; i++) {
            if (i) cout << ", ";
            cout << (*this)[i];
        }
        cout << "]\n";
    }

   private:
    void fv_val(int k) { _vals[k] = _fv(_vals[k << 1], _vals[k << 1 | 1]); }
    void add_tag(int i2, T &tag1) {
        _vals[i2] = _fm(tag1, _vals[i2]);
        if (i2 < n) tag[i2] = _ft(tag1, tag[i2]);
    }
    void push_tag(int i1) {
        add_tag(i1 << 1, tag[i1]);
        add_tag(i1 << 1 | 1, tag[i1]);
        tag[i1] = _et;
    }
    void eval(int i) {
        for (int k = logn; k >= 1; k--) push_tag(i >> k);
    }
    void eval(int l, int r) {
        for (int k = logn; k >= 1; k--) {
            if ((l >> k << k) != l) push_tag(l >> k);
            if ((r >> k << k) != r) push_tag((r - 1) >> k);
        }
    }
};

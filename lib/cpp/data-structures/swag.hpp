template <class T, T (*op)(T, T), T id>
struct SWAG {
   private:
    int sz = 0;
    vector<T> fold_l, r;
    T fold_r = id;

   public:
    SWAG() { assert(op(id, id) == id); }
    void push(T x) {
        fold_r = op(fold_r, x);
        r.push_back(x);
        sz++;
    }
    T pop() {
        assert(sz > 0);
        T res = fold();
        if (fold_l.empty()) {
            for (int i = sz - 1; i >= 0; i--) fold_l.push_back(r[i]);
            r.clear();
            fold_r = id;
            for (int i = 1; i < sz; i++) fold_l[i] = op(fold_l[i], fold_l[i - 1]);
        }
        fold_l.pop_back();
        sz--;
        return res;
    }
    T fold() {
        return fold_l.empty() ? fold_r : op(fold_l.back(), fold_r);
    }
};

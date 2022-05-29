template <class T>
struct SlopeTrick {
   public:
    static constexpr T TINF = numeric_limits<T>::max() / 3;

   private:
    T min_y = 0, add_l = 0, add_r = 0;
    priority_queue<T> ql;
    priority_queue<T, vector<T>, greater<T>> qr;

   public:
    void clear_l() {
        while (!ql.empty()) ql.pop();
    }
    void clear_r() {
        while (!qr.empty()) qr.pop();
    }
    void add_a_minus_x(T a) {
        min_y += max<T>(0, a - top_r());
        push_r(a);
        push_l(pop_r());
    }
    void add_x_minus_a(T a) {
        min_y += max<T>(0, top_l() - a);
        push_l(a);
        push_r(pop_l());
    }
    void add_abs_x_minus_a(T a) {
        add_a_minus_x(a);
        add_x_minus_a(a);
    }
    void shift_x(T x) { add_l += x, add_r += x; }
    void shift_y(T y) { min_y += y; }
    void shift_l(T l) { add_l += l; }
    void shift_r(T r) { add_r += r; }
    T get_min_y() { return min_y; }
    T get_min_x() { return ql.empty() ? qr.empty() ? 0 : top_r() : top_l(); }
    T get_fx(T x) {
        T res = min_y;
        while (!ql.empty()) res += max<T>(0, pop_l() - x);
        while (!qr.empty()) res += max<T>(0, x - pop_r());
        return res;
    }
    void merge(SlopeTrick &st) {
        if (st.size() > size()) {
            swap(st.min_y, min_y);
            swap(st.add_l, add_l);
            swap(st.add_r, add_r);
            swap(st.ql, ql);
            swap(st.qr, qr);
        }
        while (!st.qr.empty()) add_x_minus_a(st.pop_r());
        while (!st.ql.empty()) add_a_minus_x(st.pop_l());
        min_y += st.min_y;
    }
    int size() { return ql.size() + qr.size(); }

   private:
    void push_l(T a) { ql.push(a - add_l); }
    T top_l() { return ql.empty() ? -TINF : ql.top() + add_l; }
    T pop_l() {
        T top = top_l();
        if (!ql.empty()) ql.pop();
        return top;
    }
    void push_r(T a) { qr.push(a - add_r); }
    T top_r() { return qr.empty() ? TINF : qr.top() + add_r; }
    T pop_r() {
        T top = top_r();
        if (!qr.empty()) qr.pop();
        return top;
    }
};

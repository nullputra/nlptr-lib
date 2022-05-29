template <class T>
class ConvexHullTrick {
    deque<pair<T, T>> q;
    T prev_a;
    using Comp = function<bool(T, T)>;
    Comp comp;

   public:
    ConvexHullTrick(bool a_incr)
        : comp(a_incr ? Comp(less_equal<T>()) : Comp(greater_equal<T>())),
          prev_a(a_incr ? numeric_limits<T>::min() : numeric_limits<T>::max()) {}
    void add(T a, T b) {
        assert(comp(prev_a, a));
        prev_a = a;
        pair<T, T> t(a, b);
        while (q.size() > 1 && !necessary(q[q.size() - 2], q[q.size() - 1], t)) q.pop_back();
        q.push_back(t);
    }
    T get(T x) {
        assert(!q.empty());
        int ng = -1, ok = q.size() - 1;
        while (ng + 1 < ok) {
            int mid = (ng + ok) / 2;
            (comp(f(mid, x), f(mid + 1, x)) ? ng : ok) = mid;
        }
        return f(ok, x);
    }
    T get_x_incr(T x) {
        assert(!q.empty());
        while (q.size() > 1 && comp(f(0, x), f(1, x))) q.pop_front();
        return f(0, x);
    }

   private:
    bool necessary(pair<T, T> &p1, pair<T, T> &p2, pair<T, T> &p3) {
        return (__int128_t)(p2.second - p1.second) * (p2.first - p3.first) <
               (__int128_t)(p3.second - p2.second) * (p1.first - p2.first);
    }
    T f(int i, T &x) { return q[i].first * x + q[i].second; }
};

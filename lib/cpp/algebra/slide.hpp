template <class T>
vector<T> slide(const vector<T> &v, int k, bool is_mn) {
    int n = v.size();
    assert(n >= k);
    deque<int> q;
    vector<T> res;
    res.reserve(n - k + 1);
    using Comp = function<bool(T, T)>;
    Comp comp = is_mn ? Comp(greater_equal<T>()) : Comp(less_equal<T>());
    for (int i = 0; i < n; i++) {
        while (!q.empty() && comp(v[q.back()], v[i])) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) {
            res.push_back(v[q.front()]);
            if (q.front() == i - k + 1) q.pop_front();
        }
    }
    return res;
}

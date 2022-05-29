template <class T>
struct BellmanFord {
   public:
    static constexpr T TINF = numeric_limits<T>::max();

   private:
    struct Edge {
        int from, to;
        T dist;
    };
    int _n;
    vector<Edge> edges;

   public:
    BellmanFord(int n, int m) : _n(n) { edges.reserve(m); }
    void add_edge(int from, int to, T dist) {
        edges.push_back({from, to, dist});
    }
    vector<T> dists(int s = -1, int g = -1) {
        assert(-1 <= s && s < _n && -1 <= g && g < _n);
        vector<T> dists;
        if (s == -1) {
            dists.assign(_n, 0);
        } else {
            dists.assign(_n, TINF);
            dists[s] = 0;
        }
        int g_cnt = 0, lp_lim = g == -1 ? _n : _n * 2 - 1;
        for (int lp = 0; lp < lp_lim; lp++) {
            bool upd = false;
            for (auto &[from, to, dist] : edges) {
                if (dists[from] == TINF) continue;
                if (dists[to] > dists[from] + dist) {
                    dists[to] = dists[from] + dist, upd = true;
                    if (to == g && ++g_cnt >= 2) return {};
                }
            }
            if (!upd) return dists;
        }
        return g == -1 ? vector<T>{} : dists;
    }
    void print() {
#ifdef _DEBUG
        for (auto &[from, to, dist] : edges) {
            cout << "from, to, dist: " << from << ", " << to << ", " << dist << '\n';
        }
#endif
    }
};

template <class T>
struct Dinic {
   private:
    int _n;
    struct _Edge {
        int to, rev_idx;
        T cap;
    };
    vector<pair<int, int>> pos;
    vector<vector<_Edge>> edges;
    static constexpr T TINF = numeric_limits<T>::max();

   public:
    struct Edge {
        int from, to;
        T cap, flow;
    };
    Dinic(int n) : _n(n), edges(_n) {}
    void add_edge(int from, int to, T cap = 1) {
        int from_idx = edges[from].size(), to_idx = edges[to].size();
        pos.emplace_back(from, from_idx);
        if (from == to) to_idx++;
        edges[from].push_back({to, to_idx, cap});
        edges[to].push_back({from, from_idx, 0});
    }
    Edge get_edge(int i) {
        auto &e = edges[pos[i].first][pos[i].second], &re = edges[e.to][e.rev_idx];
        return Edge{pos[i].first, e.to, e.cap + re.cap, re.cap};
    }
    vector<Edge> get_edges() {
        int m = pos.size();
        vector<Edge> res;
        for (int i = 0; i < m; i++) res.push_back(get_edge(i));
        return res;
    }
    void for_each_path(const function<void(int, int, T)> &f) {
        for (auto &[from, rev_idx] : pos) {
            auto &e = edges[from][rev_idx];
            f(from, e.to, edges[e.to][e.rev_idx].cap);
        }
    }
    void change_edge(int i, T new_cap, T new_flow) {
        auto &e = edges[pos[i].first][pos[i].second], &re = edges[e.to][e.rev_idx];
        e.cap = new_cap - new_flow, re.cap = new_flow;
    }
    T flow(int s, int t, T f_lim = -1) {
        if (f_lim == -1) f_lim = TINF;
        vector<int> level(_n), cur_iter(_n);
        auto set_level = [&]() {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int from = q.front();
                q.pop();
                for (auto &e : edges[from]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[from] + 1;
                    if (e.to == t) return;
                    q.push(e.to);
                }
            }
        };
        auto try_to_flow = [&](auto self, int v, T f_in) {
            if (v == s) return f_in;
            T f_out = 0;
            for (int &i = cur_iter[v]; i < (int)edges[v].size(); i++) {
                auto &e = edges[v][i];
                if (level[v] <= level[e.to] || edges[e.to][e.rev_idx].cap == 0) continue;
                T f_part = self(self, e.to, min(f_in - f_out, edges[e.to][e.rev_idx].cap));
                if (f_part <= 0) continue;
                edges[v][i].cap += f_part, edges[e.to][e.rev_idx].cap -= f_part, f_out += f_part;
                if (f_out == f_in) break;
            }
            return f_out;
        };
        T f_res = 0;
        while (f_res < f_lim) {
            set_level();
            if (level[t] == -1) break;
            fill(cur_iter.begin(), cur_iter.end(), 0);
            while (f_res < f_lim) {
                T f_part = try_to_flow(try_to_flow, t, f_lim - f_res);
                if (!f_part) break;
                f_res += f_part;
            }
        }
        return f_res;
    }
    vector<bool> get_min_cut(int s) {
        vector<bool> reachable(_n);
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            reachable[p] = true;
            for (auto &e : edges[p]) {
                if (e.cap && !reachable[e.to]) {
                    reachable[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return reachable;
    }
    void print() {
#ifdef _DEBUG
        for (auto &[from, rev_idx] : pos) {
            auto &e = edges[from][rev_idx], &rev_e = edges[e.to][e.rev_idx];
            cout << from << "->" << e.to << " (flowed: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")\n";
        }
#endif
    }
};

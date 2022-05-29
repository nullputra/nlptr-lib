template <class T>
struct RerootingNode {
   private:
    struct Edge {
        int to, rev_idx;
        T val;
    };
    int _n, edge_num = 0;
    T _id;
    vector<T> _vals;
    vector<vector<Edge>> edges;
    using FM = function<T(T, T)>;
    const FM _merge;
    using FN = function<T(T, int)>;
    const FN _op_node;

   public:
    RerootingNode(int n, T id, const FM &merge, const FN &op_node)
        : _n(n), _id(id), _vals(_n), edges(_n), _merge(merge), _op_node(op_node) {}
    void add_edge(int u, int v) {
        edge_num++;
        int idx_u = edges[u].size(), idx_v = edges[v].size();
        edges[u].push_back({v, idx_v, _id});
        edges[v].push_back({u, idx_u, _id});
    }
    const vector<T> &vals() {
        assert(edge_num == _n - 1);
        if (_n == 1) return _vals[0] = _op_node(_id, 0), _vals;
        vector<int> par(_n, -1), ordered;
        ordered.reserve(_n);
        auto init_ordered_tree = [&](auto self, int u) -> void {
            ordered.push_back(u);
            for (auto &e : edges[u]) {
                if (e.to == par[u]) continue;
                par[e.to] = u;
                self(self, e.to);
            }
        };
        init_ordered_tree(init_ordered_tree, 0);
        for (int i = _n - 1; i > 0; i--) {
            int u = ordered[i], edge_idx = -1;
            T accum_val = _id;
            for (auto &[to, rev_idx, val] : edges[u]) {
                if (to == par[u]) {
                    edge_idx = rev_idx;
                    continue;
                }
                accum_val = _merge(accum_val, val);
            }
            edges[par[u]][edge_idx].val = _op_node(accum_val, u);
        }
        for (auto &u : ordered) {
            int sz = edges[u].size();
            vector<T> rev_accum(sz, _id);
            T accum_val = _id;
            for (int j = sz - 2; j >= 0; j--) {
                rev_accum[j] = _merge(edges[u][j + 1].val, rev_accum[j + 1]);
            }
            for (int j = 0; j < sz; j++) {
                auto &[to, rev_idx, val] = edges[u][j];
                edges[to][rev_idx].val = _op_node(_merge(accum_val, rev_accum[j]), u);
                accum_val = _merge(accum_val, val);
            }
            _vals[u] = _op_node(accum_val, u);
        }
        return _vals;
    }
    void print() {
        cout << "edges = {";
        for (int i = 0; i < _n; i++) {
            if (i) cout << ", ";
            cout << '{' << i << " -> ";
            for (int j = 0; j < (int)edges[i].size(); j++) {
                if (j) cout << ", ";
                cout << edges[i][j].to << "(val:" << edges[i][j].val << ")";
            }
            cout << '}';
        }
        cout << "}\n";
    }
};

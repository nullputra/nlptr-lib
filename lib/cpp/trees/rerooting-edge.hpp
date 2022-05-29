template <class Val, class Key>
struct RerootingEdge {
    struct Edge {
        int to;
        Key key;
        Val val, n_val;
    };
    const Val _id;
    vector<vector<Edge>> edges;
    using F = function<Val(Val, Val)>;
    using G = function<Val(Val, Key)>;
    const F _merge;
    const G _op_edge;
    vector<Val> sub_val, _vals;
    RerootingEdge(int n, Val id, const F &merge, const G &op_edge)
        : _id(id), edges(n), _merge(merge), _op_edge(op_edge), sub_val(n, _id), _vals(n, _id) {}
    void add_edge(int u, int v, Key k) {
        edges[u].push_back({v, k, _id, _id});
        edges[v].push_back({u, k, _id, _id});
    }
    void add_edge_bi(int u, int v, Key k1, Key k2) {
        edges[u].push_back({v, k1, _id, _id});
        edges[v].push_back({u, k2, _id, _id});
    }
    vector<Val> vals() {
        auto dfs_sub = [&](auto self, int idx, int par) -> void {
            for (auto &e : edges[idx]) {
                if (e.to == par) continue;
                self(self, e.to, idx);
                sub_val[idx] = _merge(sub_val[idx], _op_edge(sub_val[e.to], e.key));
            }
        };
        dfs_sub(dfs_sub, 0, -1);
        auto dfs_all = [&](auto self, int idx, int par, Val top) -> void {
            Val buff = _id;
            for (int i = 0; i < (int)edges[idx].size(); i++) {
                auto &e = edges[idx][i];
                e.n_val = buff;
                e.val = _op_edge(par == e.to ? top : sub_val[e.to], e.key);
                buff = _merge(buff, e.val);
            }
            _vals[idx] = buff;
            buff = _id;
            for (int i = edges[idx].size() - 1; i >= 0; i--) {
                auto &e = edges[idx][i];
                if (e.to != par) self(self, e.to, idx, _merge(e.n_val, buff));
                e.n_val = _merge(e.n_val, buff);
                buff = _merge(buff, e.val);
            }
        };
        dfs_all(dfs_all, 0, -1, _id);
        return _vals;
    }
};

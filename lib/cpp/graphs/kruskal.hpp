#include "data-structures/union-find.hpp"
template <class T>
struct Kruskal {
   public:
    struct Edge {
        int u, v;
        T cost;
        bool operator<(const Edge &rhs) { return cost < rhs.cost; }
    };
    vector<Edge> mst;
    T cost_tot = 0;

   private:
    int _n;
    vector<Edge> edges;

   public:
    Kruskal(int n, int m) : _n(n) { edges.reserve(m); }
    void add_edge(int u, int v, T c) { edges.push_back({u, v, c}); }
    int build(bool builds_mst = false) {
        sort(edges.begin(), edges.end());
        UnionFind uf(_n);
        for (auto &e : edges) {
            if (!uf.same(e.u, e.v)) {
                uf.merge(e.u, e.v);
                if (builds_mst) mst.push_back(e);
                cost_tot += e.cost;
            }
        }
        return uf.size(edges[0].u);
    }
};

template <class T>
struct Edge {
    int to;
    T dist;
};
template <class T>
Edge<T> farthest(vector<vector<Edge<T>>> &edges, int v1, int v0 = -1) {
    Edge<T> res{v1, 0};
    for (auto &[v2, dist] : edges[v1]) {
        if (v0 == v2) continue;
        auto nxt = farthest(edges, v2, v1);
        nxt.dist += dist;
        if (res.dist < nxt.dist) res = nxt;
    }
    return res;
}
template <class T>
T diameter(vector<vector<Edge<T>>> &edges) {
    return farthest(edges, farthest(edges, 0).to).dist;
}

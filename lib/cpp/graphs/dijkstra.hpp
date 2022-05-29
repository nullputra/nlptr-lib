template <class Cost>
class Dijkstra {
   private:
    int _n;
    bool _directed;

   public:
    struct Edge {
        int to;
        Cost cost;
    };
    vector<vector<Edge>> edges;
    vector<Cost> _dists;
    const Cost COST_INF = numeric_limits<Cost>::max();
    Dijkstra(int n, bool directed = false) : _n(n), _directed(directed), edges(_n) {}
    void add_edge(int from, int to, Cost cost) {
        edges[from].push_back({to, cost});
        if (!_directed) edges[to].push_back({from, cost});
    }
    vector<Cost> dists(int s = 0) {
        _dists.assign(_n, COST_INF);
        _dists[s] = 0;
        priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<pair<Cost, int>>> q;
        q.emplace(_dists[s], s);
        while (!q.empty()) {
            auto [prev_d, v] = q.top();
            q.pop();
            if (prev_d > _dists[v]) continue;
            for (auto &e : edges[v]) {
                Cost nxt_dis = _dists[v] + e.cost;
                if (_dists[e.to] > nxt_dis) {
                    _dists[e.to] = nxt_dis;
                    q.emplace(_dists[e.to], e.to);
                }
            }
        }
        return _dists;
    }
};

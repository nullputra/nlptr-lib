template <class T>
struct Prim {
    T cost_tot = 0;
    static constexpr T TINF = numeric_limits<T>::max();
    Prim(vector<vector<T>> &adja) {
        int n = adja.size();
        vector<T> min_cost(n, TINF);
        min_cost[0] = 0;
        vector<bool> vis(n);
        while (true) {
            int from = -1;
            for (int u = 0; u < n; u++) {
                if (!vis[u] && (from == -1 || min_cost[u] < min_cost[from])) from = u;
            }
            if (from == -1) break;
            vis[from] = true;
            cost_tot += min_cost[from];
            for (int to = 0; to < n; to++) {
                if (adja[from][to] != -1) min_cost[to] = min(min_cost[to], adja[from][to]);
            }
        }
    }
};

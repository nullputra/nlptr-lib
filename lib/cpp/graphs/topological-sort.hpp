vector<int> topological_sort(vector<vector<int>> &edges) {
    int n = edges.size();
    vector<int> cnt(n);
    for (int v1 = 0; v1 < n; v1++) {
        for (auto &v2 : edges[v1]) cnt[v2]++;
    }
    queue<int> q;
    for (int v = 0; v < n; v++) {
        if (cnt[v] == 0) q.push(v);
    }
    vector<int> sorted;
    sorted.reserve(n);
    while (!q.empty()) {
        int v1 = q.front();
        q.pop();
        sorted.push_back(v1);
        if ((int)sorted.size() == n) return sorted;
        for (auto &v2 : edges[v1]) {
            if (--cnt[v2] == 0) q.push(v2);
        }
    }
    return {};
}

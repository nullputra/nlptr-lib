template <class T>
T traveling_salesman_problem(const vector<vector<T>> &dist) {
    constexpr T TINF = numeric_limits<T>::max() / 3;
    int n = dist.size(), all_bit = (1 << n) - 1;
    assert(1 <= n && n <= 30);
    vector dp(1 << n, vector(n, TINF));
    for (int v = 0; v < n; v++) dp[1 << v][v] = 0;
    auto rec = [&](auto self, int s1, int v1) -> T {
        if (dp[s1][v1] != TINF) return dp[s1][v1];
        int s0 = s1 ^ (1 << v1);
        for (int v0 = 0; v0 < n; v0++) {
            if (s0 & (1 << v0) && dist[v0][v1] < TINF) dp[s1][v1] = min(dp[s1][v1], self(self, s0, v0) + dist[v0][v1]);
        }
        if (dp[s1][v1] > TINF) dp[s1][v1] = TINF;
        return dp[s1][v1];
    };
    T res = TINF;
    for (int v1 = 0; v1 < n; v1++) res = min(res, rec(rec, all_bit, v1));
    return res;
}

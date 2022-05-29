#include <bits/stdc++.h>
using namespace std;

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0304"
#include "graphs/bellman-ford.hpp"

int main() {
    int n, c;
    cin >> n >> c;
    vector<int> a(c), o(c), b(c), s(c), d(c), undefined;
    for (int i = 0; i < c; i++) {
        char ch_o[5], ch_s[5];
        assert(scanf("%d%[^0123456789]%d%[^0123456789]%d", &a[i], ch_o, &b[i], ch_s, &d[i]));
        a[i]--, b[i]--;
        if (ch_o[0] == '<') o[i] = 0;
        if (ch_o[0] == '>') o[i] = 1;
        if (ch_o[0] == '*') o[i] = 2, undefined.push_back(i);
        if (ch_s[0] == '+') s[i] = 0;
        if (ch_s[0] == '-') s[i] = 1;
    }
    int ans = -1;
    for (int bit = 0; bit < (1 << undefined.size()); bit++) {
        for (int k = 0; k < (int)undefined.size(); k++) {
            o[undefined[k]] = (bit >> k) & 1;
        }
        BellmanFord<int> bf(n, c * 2);
        for (int i = 0; i < c; i++) {
            if (o[i] == 1) swap(a[i], b[i]);
            bf.add_edge(b[i], a[i], 0);
            if (s[i] == 0) bf.add_edge(b[i], a[i], -d[i]);
            if (s[i] == 1) bf.add_edge(a[i], b[i], d[i]);
            if (o[i] == 1) swap(a[i], b[i]);
        }
        auto dists = bf.dists(0);
        if (dists.empty()) continue;
        if (any_of(dists.begin(), dists.end(), [](int &x) { return x < 0; })) continue;
        for (auto &dist : dists) ans = max(ans, dist);
    }
    if (ans == BellmanFord<int>::TINF) {
        cout << "inf\n";
    } else {
        cout << ans << '\n';
    }
}

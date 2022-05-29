#include <bits/stdc++.h>
using namespace std;

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2207"
#include "data-structures/weighted-union-find.hpp"

int main() {
    while (true) {
        int n;
        cin >> n;
        if (!n) break;
        WeightedUnionFind<int> uf(n * 2);
        map<string, int> mp;
        int cnt = 0;
        bool valid = true;
        for (int i = 0; i < n; i++) {
            string _, s1, sdiff, s2;
            cin >> _ >> s1 >> _ >> sdiff >> s2;
            if (!mp.count(s1)) mp[s1] = cnt++;
            int id1 = mp[s1];
            if (!mp.count(s2)) mp[s2] = cnt++;
            int id2 = mp[s2];
            int diff = stoi(sdiff.substr(3));
            if (uf.same(id1, id2)) {
                if (diff != uf.diff(id1, id2)) valid = false;
            } else {
                uf.merge(id1, id2, diff);
            }
        }
        cout << (valid ? "Yes" : "No") << '\n';
    }
    return 0;
}

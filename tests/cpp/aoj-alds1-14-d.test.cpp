#include <bits/stdc++.h>
using namespace std;

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja"
#include "strings/sa-is.hpp"

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    string s;
    cin >> s;
    SA_IS sa_is(s);
    int q;
    cin >> q;
    string p;
    for (int i = 0; i < q; i++) {
        cin >> p;
        cout << sa_is.contains(p) << '\n';
    }
}

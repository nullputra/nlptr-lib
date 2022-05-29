#include <bits/stdc++.h>
using namespace std;

#define PROBLEM "https://yukicoder.me/problems/447"
#include "algebra/chinese-remainder-theorem.hpp"

int main() {
    vector<ll> x(3), y(3);
    bool exist_non_zero = false;
    for (int i = 0; i < 3; i++) {
        cin >> x[i] >> y[i];
        if (x[i]) exist_non_zero = true;
    }
    auto [r, m] = crt(x, y);
    if (m == -1) {
        cout << -1 << '\n';
        return 0;
    }
    cout << (exist_non_zero ? r : m) << '\n';
    return 0;
}

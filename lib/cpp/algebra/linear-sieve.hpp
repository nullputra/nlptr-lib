struct LinearSieve {
    int _n;
    vector<int> min_factors, primes, mob;
    LinearSieve(int n, bool calcs_mob = false) : _n(n), min_factors(_n + 1) {
        iota(min_factors.begin(), min_factors.end(), 0);
        if (calcs_mob) mob.assign(_n + 1, -1), mob[1] = 1;
        for (int i = 2; i <= _n; i++) {
            if (min_factors[i] == i) primes.push_back(i);
            int p_lim = min(min_factors[i], _n / i);
            for (auto &p : primes) {
                if (p > p_lim) break;
                min_factors[i * p] = p;
                if (calcs_mob) mob[i * p] = min_factors[i] == p ? 0 : -mob[i];
            }
        }
    }
    vector<pair<int, int>> factorize(int x) {
        assert(0 < x && x <= _n);
        vector<pair<int, int>> factors;
        for (int cur = min_factors[x], ex = 0;; ex++, x /= min_factors[x]) {
            if (cur != min_factors[x]) {
                factors.emplace_back(cur, ex);
                if (x == 1) break;
                cur = min_factors[x], ex = 0;
            }
        }
        return factors;
    }
    vector<int> divisors(int x, bool sorted = false) {
        vector<int> divs{1};
        vector<pair<int, int>> factors = factorize(x);
        for (auto &[b, ex] : factors) {
            int sz = divs.size();
            for (int i = 0; i < sz; i++) {
                int mul = divs[i];
                for (int j = 0; j < ex; j++) divs.push_back(mul *= b);
            }
        }
        if (sorted) sort(divs.begin(), divs.end());
        return divs;
    }
    template <class T>
    T f1(vector<T> &F) {
        int sz = F.size();
        assert(sz - 1 <= _n && !mob.empty());
        T res = 0;
        for (int i = 0; i < sz; i++) res += F[i] * mob[i];
        return res;
    }
    template <class T>
    void zeta(vector<T> &f) {
        int sz = f.size();
        assert(sz - 1 <= _n);
        for (auto &p : primes) {
            if (p >= sz) break;
            for (int i = (sz - 1) / p; i >= 1; i--) f[i] += f[i * p];
        }
    }
    template <class T>
    void mobius(vector<T> &F) {
        int sz = F.size();
        assert(sz - 1 <= _n);
        for (auto &p : primes) {
            if (p >= sz) break;
            for (int i = 1; i * p < sz; i++) F[i] -= F[i * p];
        }
    }
    template <class T>
    vector<T> gcd_conv(vector<T> f, vector<T> g, bool is_square = false) {
        int sz = max(f.size(), g.size());
        f.resize(sz, 0), g.resize(sz, 0);
        zeta(f);
        is_square ? void(g = f) : zeta(g);
        vector<T> H(sz);
        for (int i = 1; i < sz; i++) H[i] = f[i] * g[i];
        mobius(H);
        return H;
    }
};

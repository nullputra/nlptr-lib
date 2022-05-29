using ull = unsigned long long;
struct RollingHash {
   private:
    int n;
    ull base = 127;
    vector<ull> hash, pw;
    static constexpr ull M30 = (1ull << 30) - 1, M31 = (1ull << 31) - 1, M61 = (1ull << 61) - 1;

   public:
    RollingHash() {}
    RollingHash(string &s, bool randomizes = false) : n(s.size()), hash(n + 1), pw(n + 1, 1) {
        if (randomizes) randomize_base();
        for (int i = 0; i < n; i++) {
            hash[i + 1] = mod(mul(hash[i], base) + s[i]), pw[i + 1] = mod(mul(pw[i], base));
        }
    }
    ull slice(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return mod(hash[r] + M61 * 4 - mul(hash[l], pw[r - l]));
    }
    int get_lcp(int a, int b) {
        int ok = 0, ng = n - max(a, b);
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            (slice(a, a + mid) == slice(b, b + mid) ? ok : ng) = mid;
        }
        return ok;
    }
    int get_lcp(int a, RollingHash &rh, int b) {
        int ok = 0, ng = min(n - a, rh.n - b);
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            (slice(a, a + mid) == rh.slice(b, b + mid) ? ok : ng) = mid;
        }
        return ok;
    }

   private:
    void randomize_base() {
        random_device rnd;
        int k = int(rnd()) % 2022 + 128;
        base = [&](ull x, int m) {
            ull res = 1;
            while (m) {
                if (m & 1) res = mod(mul(res, x));
                x = mod(mul(x, x)), m /= 2;
            }
            return res;
        }(3, k);
        while (gcd(M61 - 1, k++) > 1) base = mod(mul(base, 3));
    }
    ull mod(ull x) { return x = (x >> 61) + (x & M61), x >= M61 ? x - M61 : x; }
    ull mul(ull a, ull b) {
        ull a0 = a >> 31, a1 = a & M31, b0 = b >> 31, b1 = b & M31, mid = a1 * b0 + a0 * b1;
        return a0 * b0 * 2 + (mid >> 30) + ((mid & M30) << 31) + a1 * b1;
    }
};

#include "algebra/modular.hpp"

template <int m>
struct NumberTheoreticTransform {
   private:
    vector<int> rev{0, 1};
    vector<mint> rts{0_M, 1_M};
    // vector<mint> rts;
    int base = 1, max_base = 0;
    mint root = 2;

   public:
    constexpr NumberTheoreticTransform() {
        // rts.push_back(0);
        // rts.push_back(1);
        assert(m >= 3 && m % 2 == 1);
        int tmp = m - 1;
        while (tmp % 2 == 0) tmp >>= 1, max_base++;
        while (root.pow((m - 1) >> 1) == 1_M) root++;
        assert(root.pow(m - 1) == 1_M);
        root = root.pow((m - 1) >> max_base);
    }
    void ntt(vector<mint> &f) {
        int n = f.size(), zeros = __builtin_ctz(n), shift = base - zeros;
        assert((n & (n - 1)) == 0);
        ensure_base(zeros);
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) swap(f[i], f[rev[i] >> shift]);
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; ++j) {
                    mint z = f[i + j + k] * rts[j + k];
                    f[i + j + k] = f[i + j] + m - z;
                    f[i + j] = f[i + j] + z;
                }
            }
        }
    }
    vector<mint> conv(vector<mint> f, vector<mint> g, bool is_square = false) {
        int h_deg = f.size() + g.size() - 1, n_base = 1;
        while ((1 << n_base) < h_deg) n_base++;
        ensure_base(n_base);
        int sz = 1 << n_base;
        f.resize(sz, 0), g.resize(sz, 0);
        ntt(f);
        is_square ? void(g = f) : ntt(g);
        mint sz_inv = mint(sz).inv();
        for (int i = 0; i < sz; i++) f[i] *= g[i] * sz_inv;
        reverse(f.begin() + 1, f.end());
        ntt(f);
        f.resize(h_deg);
        return f;
    }

   private:
    void ensure_base(int n_base) {
        if (n_base <= base) return;
        rev.resize(1 << n_base), rts.resize(1 << n_base);
        for (int i = 0; i < (1 << n_base); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (n_base - 1));
        }
        assert(n_base <= max_base);
        while (base < n_base) {
            mint z = root.pow(1 << (max_base - 1 - base));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                rts[i << 1] = rts[i];
                rts[(i << 1) + 1] = rts[i] * z;
            }
            base++;
        }
    }
};
NumberTheoreticTransform<MOD> NTT;

#include "algebra/modular.hpp"

struct LagrangeInterpolation {
    int d;
    vector<mint> a;
    LagrangeInterpolation(vector<mint> &v) : d(v.size() - 1), a(d + 1) {
        vector<mint> f(d + 1, 1);
        for (int i = 1; i < d + 1; i++) f[i] = f[i - 1] * i;
        for (int i = 0; i <= d; i++) {
            a[i] = v[i] / (f[i] * f[d - i]);
            if ((d - i) & 1) a[i] *= -1;
        }
    }
    mint operator()(mint x) {
        vector<mint> r(d + 1, 1);
        for (int i = d - 1; i >= 0; i--) r[i] = r[i + 1] * (x - i - 1);
        mint l = 1, res;
        for (int i = 0; i <= d; i++) res += a[i] * l * r[i], l *= x - i;
        return res;
    }
};

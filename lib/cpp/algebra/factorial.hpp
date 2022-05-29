#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include "algebra/modular.hpp"

struct Factorial {
    int fact_size = 1, inv_size = 2;
    vector<mint> fact{1}, inv_fact{1}, inv{0, 1};
    void expand_fact(int mx) {
        while (fact_size <= mx) {
            fact.resize(2 * fact_size);
            inv_fact.resize(2 * fact_size);
            for (int i = fact_size; i < 2 * fact_size; i++) fact[i] = fact[i - 1] * i;
            inv_fact[2 * fact_size - 1] = fact[2 * fact_size - 1].inv();
            for (int i = 2 * fact_size - 1; i >= fact_size + 1; i--) inv_fact[i - 1] = inv_fact[i] * i;
            fact_size *= 2;
        }
    }
    void expand_inv(int mx) {
        while (inv_size <= mx) {
            inv.resize(2 * inv_size);
            for (int i = inv_size; i < 2 * inv_size; i++) {
                inv[i] = (mint::mod() - mint::mod() / i) * inv[mint::mod() % i];
            }
            inv_size *= 2;
        }
    }
} _ft;
mint fact(int n) {
    assert(n >= 0);
    internal::_ft.expand_fact(n);
    return internal::_ft.fact[n];
}
mint inv_fact(int n) {
    assert(n >= 0);
    internal::_ft.expand_fact(n);
    return internal::_ft.inv_fact[n];
}
mint comb(int n, int r) {
    assert(n >= 0 && r >= 0);
    return n < r ? 0 : fact(n) * inv_fact(r) * inv_fact(n - r);
}
mint perm(int n, int r) {
    assert(n >= 0 && r >= 0);
    return n < r ? 0 : fact(n) * inv_fact(n - r);
}
mint homo(int n, int r) {
    return comb(n + r - 1, r);
}
mint catalan(int n) {
    return fact(n * 2) * inv_fact(n) * inv_fact(n + 1);
}
mint inv(int n) {
    assert(n > 0);
    internal::_ft.expand_inv(n);
    return internal::_ft.inv[n];
}

#endif  // FACTORIAL_HPP

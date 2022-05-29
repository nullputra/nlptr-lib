#ifndef MODULAR_HPP
#define MODULAR_HPP

template <int m>
struct Modular {
   private:
    uint _v;
    using mint = Modular;

   public:
    constexpr Modular() : _v(0) {}
    constexpr Modular(long long v) {
        v %= 1ll * m;
        _v = v < 0 ? v + m : v;
    };
    mint &operator++() {
        if (++_v == umod()) _v = 0;
        return *this;
    }
    mint &operator--() {
        if (_v == 0) _v = umod();
        return _v--, *this;
    }
    mint operator++(int) {
        mint res = *this;
        return ++*this, res;
    }
    mint operator--(int) {
        mint res = *this;
        return --*this, res;
    }
    constexpr mint operator-() { return mint() - *this; }
    mint operator+(const mint &rhs) { return mint(*this) += rhs; }
    mint operator-(const mint &rhs) { return mint(*this) -= rhs; }
    mint operator*(const mint &rhs) { return mint(*this) *= rhs; }
    mint operator/(const mint &rhs) { return mint(*this) /= rhs; }
    mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        _v = 1ll * _v * rhs._v % umod();
        return *this;
    }
    mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }
    friend mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
    friend mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
    bool operator==(const mint &rhs) { return this->_v == rhs._v; }
    bool operator!=(const mint &rhs) { return this->_v != rhs._v; }
    static constexpr int mod() { return m; }
    constexpr uint val() const { return _v; }
    mint pow(long long n) const {
        mint x = *this, res = 1;
        while (n) {
            if (n & 1) res *= x;
            x *= x, n /= 2;
        }
        return res;
    }
    mint inv() const { return pow(umod() - 2); }
    friend istream &operator>>(istream &is, mint &x) {
        long long _v;
        return is >> _v, x = _v, is;
    }
    friend ostream& operator<<(ostream& os, const mint& x) { return os << x.val(); }

   private:
    static constexpr uint umod() { return m; }
};
using mint = Modular<MOD>;
constexpr mint operator""_M(unsigned long long x) { return mint(x); }

#endif  // MODULAR_HPP

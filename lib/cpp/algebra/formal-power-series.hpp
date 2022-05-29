#include "conv/number-theoretic-transform.hpp"

template <class T>
struct FormalPowerSeries : public vector<T> {
   public:
    using vector<T>::operator=;
    using FPS = FormalPowerSeries;
    FormalPowerSeries() {}
    FormalPowerSeries(vector<T> &v) : vector<T>(v) { shrink(); }
    FormalPowerSeries(initializer_list<T> list) : vector<T>(list) { shrink(); }
    FPS &operator+=(const FPS &rhs) {
        if (size() < rhs.size()) this->resize(rhs.size());
        for (int i = 0; i < rhs.size(); i++) (*this)[i] += rhs.freq(i);
        return shrink();
    }
    FPS &operator-=(const FPS &rhs) {
        if (size() < rhs.size()) this->resize(rhs.size());
        for (int i = 0; i < rhs.size(); i++) (*this)[i] -= rhs[i];
        return shrink();
    }
    FPS &operator*=(const FPS &rhs) {
        *this = NTT.conv(*this, rhs);
        return shrink();
    }
    FPS &operator*=(const T &r) {
        for (int i = 0; i < size(); i++) (*this)[i] *= r;
        return shrink();
    }
    FPS &operator<<=(int s) {
        this->insert(this->begin(), s, T(0));
        return shrink();
    }
    FPS &operator>>=(int s) {
        if (size() <= s) return FPS();
        this->erase(this->begin(), this->begin() + s);
        return shrink();
    }
    mint &operator[](int p) {
        if (size() < p) this->resize(p + 1);
        return vector<T>::operator[](p);
    }
    friend FPS operator+(const FPS &lhs, const FPS &rhs) { return FPS(lhs) += rhs; }
    friend FPS operator-(const FPS &lhs, const FPS &rhs) { return FPS(lhs) -= rhs; }
    friend FPS operator*(const FPS &lhs, const FPS &rhs) { return FPS(lhs) *= rhs; }
    friend FPS operator<<(const FPS &lhs, const int s) { return FPS(lhs) <<= s; }
    friend FPS operator>>(const FPS &lhs, const int s) { return FPS(lhs) >>= s; }
    FPS integral() const {
        vector<T> res(size() + 1);
        for (int i = 0; i < size(); i++) res[i + 1] = (*this)[i] / (i + 1);
        return res;
    }
    T eval(T x) const {
        T sum = 0, base = 1;
        for (int i = 0; i < size(); i++) sum += base * (*this)[i], base *= x;
        return sum;
    }
    int size() const { return vector<T>::size(); }
    friend ostream &operator<<(ostream &os, const FPS &pol) {
#ifdef _DEBUG
        if (!pol.size()) return os << '0';
        for (int i = 0; i < pol.size(); i++) {
            if (pol[i].val()) {
                os << pol[i].val() << "x^" << i;
                if (i != pol.size() - 1) os << '+';
            }
        }
#endif
        return os;
    }

   private:
    T freq(int p) const {
        return size() < p ? 0 : vector<T>::operator[](p);
    }
    FPS &shrink() {
        while (size() && this->back() == 0) this->pop_back();
        return *this;
    }
};
using FPS = FormalPowerSeries<mint>;

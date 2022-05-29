template <class T>
struct Rational {
   public:
//    private:
    T _nume, _deno;

//    public:
    Rational(T n = 0, T d = 1) : _nume(n), _deno(d) { normalize(); }
    Rational &operator=(T n) { return assign(n, 1); }
    Rational &assign(T n = 0, T d = 1) { return _nume = n, _deno = d, normalize(), *this; }
    T nume() const { return _nume; }
    T deno() const { return _deno; }
    Rational &operator+=(Rational &r) {
        T g = gcd(_deno, r._deno);
        _deno /= g, _nume = _nume * (r._deno / g) + r._nume * _deno;
        g = gcd(_nume, g), _nume /= g, _deno *= r._deno / g;
        return *this;
    }
    Rational &operator-=(const Rational &r) {
        T g = gcd(_deno, r._deno);
        _deno /= g, _nume = _nume * (r._deno / g) - r._nume * _deno;
        g = gcd(_nume, g), _nume /= g, _deno *= r._deno / g;
        return *this;
    }
    Rational &operator*=(const Rational &r) {
        T g1 = gcd(_nume, r._deno), g2 = gcd(_deno, r._nume);
        _nume = (_nume / g1) * (r._nume / g2), _deno = (_deno / g2) * (r._deno / g1);
        return *this;
    }
    Rational &operator/=(const Rational &r) {
        T g1 = gcd(_nume, r._nume), g2 = gcd(_deno, r._deno);
        _nume = (_nume / g1) * (r._deno / g2), _deno = (_deno / g2) * (r._nume / g1);
        if (_deno < 0) _nume = -_nume, _deno = -_deno;
        return *this;
    }
    Rational &operator+=(const T &i) { return (*this) += Rational{i}; }
    Rational &operator-=(const T &i) { return (*this) -= Rational{i}; }
    Rational &operator*=(const T &i) { return (*this) *= Rational{i}; }
    Rational &operator/=(const T &i) { return (*this) /= Rational{i}; }
    Rational operator+(const Rational &r) const { return Rational(*this) += r; }
    Rational operator-(const Rational &r) const { return Rational(*this) -= r; }
    Rational operator*(const Rational &r) const { return Rational(*this) *= r; }
    Rational operator/(const Rational &r) const { return Rational(*this) /= r; }
    Rational operator+(const T &i) const { return Rational(*this) += i; }
    Rational operator-(const T &i) const { return Rational(*this) -= i; }
    Rational operator*(const T &i) const { return Rational(*this) *= i; }
    Rational operator/(const T &i) const { return Rational(*this) /= i; }
    Rational operator-() const { return Rational{-_nume, _deno}; }
    Rational &operator++() { return _nume += _deno, *this; }
    Rational &operator--() { return _nume -= _deno, *this; }
    bool operator==(const Rational &r) const { return _nume * r._deno == r._nume * _deno; }
    bool operator!=(const Rational &r) const { return _nume * r._deno != r._nume * _deno; }
    bool operator<(const Rational &r) const { return _nume * r._deno < r._nume * _deno; }
    bool operator>(const Rational &r) const { return _nume * r._deno > r._nume * _deno; }
    bool operator<=(const Rational &r) const { return _nume * r._deno <= r._nume * _deno; }
    bool operator>=(const Rational &r) const { return _nume * r._deno >= r._nume * _deno; }
    template <class Real = double>
    Real to_double() const { return Real(_nume) / _deno; }
    Rational abs() const { return Rational{_nume > 0 ? _nume : -_nume, _deno}; }
    friend ostream &operator<<(ostream &os, const Rational &r) {
        return os << r._nume << '/' << r._deno, os;
    }

   private:
    static T gcd(T a, T b) { return __gcd(a > 0 ? a : a, b > 0 ? b : b); }
    void normalize() {
        if (_nume == 0) return _deno = 1, void();
        if (_nume == 1 || _deno == 1) return;
        T g = gcd(_nume, _deno);
        _nume /= g, _deno /= g;
        if (_deno < 0) _nume = -_nume, _deno = -_deno;
    }
};

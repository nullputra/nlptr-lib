struct Com {
    double re, im;
    constexpr Com() : re(), im() {}
    constexpr Com(double _re, double _im) : re(_re), im(_im) {}
    double real() { return re; }
    double imag() { return im; }
    Com operator+(Com &c) { return {re + c.re, im + c.im}; }
    Com operator-(Com &c) { return {re - c.re, im - c.im}; }
    Com operator*(Com &c) { return {re * c.re - im * c.im, re * c.im + im * c.re}; }
    Com operator/(double d) { return {re / d, im / d}; }
    Com &operator*=(Com &c) { return *this = (*this) * c; }
    Com &operator/=(double d) { return *this = (*this) / d; }
    friend Com conj(Com c) { return {c.re, -c.im}; }
};
struct Angles {
    static constexpr int I_MAX = 30;
    Com z[I_MAX];
    constexpr Angles() : z() {
        for (int i = 0; i < I_MAX; i++) {
            double ang = 2 * M_PI / (1 << (i + 1));
            z[i] = {cos(ang), sin(ang)};
        }
    }
    Com operator[](int i) const {
        assert(0 <= i && i < I_MAX);
        return z[i];
    }
};
constexpr Angles ang;
void fft(vector<Com> &f, bool is_inverse) {
    int n = f.size();
    for (int i = 0, j = 1; j < n; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1) {}
        if (i > j) swap(f[i], f[j]);
    }
    for (int k = 0, t = 1; t < n; ++k, t <<= 1) {
        Com bw = is_inverse ? conj(ang[k]) : ang[k];
        for (int i = 0; i < n; i += t * 2) {
            Com w(1, 0);
            for (int j = 0; j < t; j++) {
                int l = i + j, r = i + j + t;
                Com c = f[l], d = f[r] * w;
                f[l] = c + d, f[r] = c - d, w *= bw;
            }
        }
    }
    if (is_inverse) {
        for (int i = 0; i < n; i++) f[i] /= n;
    }
}
template <class T>
vector<T> conv(const vector<T> &f, const vector<T> &g, bool is_square = false) {
    int f_deg = f.size(), g_deg = g.size(), n = 1;
    while (n < f_deg + g_deg) n <<= 1;
    vector<Com> _f(n, Com(0, 0)), _g(n, Com(0, 0));
    for (int i = 0; i < f_deg; i++) _f[i] = {(double)f[i], 0};
    for (int i = 0; i < g_deg; i++) _g[i] = {(double)g[i], 0};
    fft(_f, false);
    is_square ? void(_g = _f) : fft(_g, false);
    for (int i = 0; i < n; i++) _f[i] *= _g[i];
    fft(_f, true);
    int h_deg = f_deg + g_deg - 1;
    vector<T> h(h_deg);
    for (int i = 0; i < h_deg; i++) h[i] = (T)round(_f[i].real());
    return h;
}

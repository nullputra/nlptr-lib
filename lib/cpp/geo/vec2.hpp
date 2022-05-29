constexpr double EPS = 1e-10;
template <class T>
enable_if_t<is_integral_v<T>, int> sgn(T a) { return (a > 0) - (a < 0); }
template <class T>
enable_if_t<is_floating_point_v<T>, int> sgn(T a) { return (a > EPS) - (a < -EPS); }
template <class T>
struct Vec2 {
    T x, y;
    Vec2(){};
    Vec2(T _x, T _y) : x(_x), y(_y) {}
    Vec2 operator+() const { return *this; }
    Vec2 operator-() const { return {-x, -y}; }
    Vec2 operator+(const Vec2 &v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2 &v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(T s) const { return {x * s, y * s}; }
    Vec2 operator/(T s) const {
        assert(s != 0);
        return {x / s, y / s};
    }
    Vec2 &operator+=(const Vec2 &v) {
        x += v.x, y += v.y;
        return *this;
    }
    Vec2 &operator-=(const Vec2 &v) {
        x -= v.x, y -= v.y;
        return *this;
    }
    Vec2 &operator*=(T s) {
        x *= s, y *= s;
        return *this;
    }
    bool operator==(const Vec2 &v) { return sgn(x - v.x) == 0 && sgn(y - v.y) == 0; }
    bool operator!=(const Vec2 &v) { return !(*this == v); }
    bool operator<(const Vec2 &v) { return sgn(x - v.x) ? sgn(x - v.x) < 0 : sgn(y - v.y) < 0; }
    double len() const { return sqrt(len_sq()); }
    T len_sq() const { return x * x + y * y; }
    T dot(const Vec2 &v) const { return x * v.x + y * v.y; }
    T cross(const Vec2 &v) const { return x * v.y - y * v.x; }
    Vec2 rotate(double arg) const {
        assert(is_floating_point_v<T>);
        double cs = cos(arg), sn = sin(arg);
        return {x * cs - y * sn, x * sn + y * cs};
    }
    double angle() const { return atan2(y, x); }
    Vec2 normalized() const {
        assert(is_floating_point_v<T>);
        return *this / len();
    }
    Vec2 normal_unitized() const {
        assert(is_floating_point_v<T>);
        return {-normalized().y, normalized().x};
    }
    friend Vec2 operator*(T s, const Vec2 &v) { return {s * v.x, s * v.y}; }
    friend istream &operator>>(istream &is, Vec2 &v) { return is >> v.x >> v.y; }
    friend ostream &operator<<(ostream &os, const Vec2 &v) { return os << v.x << ' ' << v.y; }
};
template <class T>
T manhattan_dis(Vec2<T> &v1, Vec2<T> &v2) {
    Vec2<T> diff = v1 - v2;
    return abs(diff.x) + abs(diff.y);
}
template <class T>
int inter_seg_pt(const Vec2<T> &a1, const Vec2<T> &a2, const Vec2<T> &b) {
    int f = sgn((a2 - a1).cross(b - a1));
    if (f) return f;
    if (sgn((a2 - a1).dot(b - a1)) < 0) return -2;
    if (sgn((a1 - a2).dot(b - a2)) < 0) return 2;
    return 0;
}
template <class T>
long double angle(const Vec2<T> &a, const Vec2<T> &b, const Vec2<T> &c) {
    long double ang = (c - b).angle() - (a - b).angle();
    return ang < 0 ? ang + M_PI * 2 : ang;
}
template <class T>
int angle_type(const Vec2<T> &a, const Vec2<T> &b, const Vec2<T> &c) { return -sgn((a - b).dot(c - b)); }
template <class T>
int intersect_type(const Vec2<T> &a1, const Vec2<T> &a2, const Vec2<T> &b1, const Vec2<T> &b2) {
    if ((a2 - a1).cross(b2 - b1) > EPS) return 1;
    return ((a2 - a1).cross(b1 - a1) > EPS) ? 0 : 2;
}
template <class T>
bool is_intersect_seg(const Vec2<T> &a1, const Vec2<T> &a2, const Vec2<T> &b1, const Vec2<T> &b2) {
    return inter_seg_pt(a1, a2, b1) * inter_seg_pt(a1, a2, b2) <= 0 && inter_seg_pt(b1, b2, a1) * inter_seg_pt(b1, b2, a2) <= 0;
}
template <class T>
bool is_intersect_seg_ray(const Vec2<T> &a1, const Vec2<T> &a2, const Vec2<T> &b, const double b_arg) {
    return angle(a1, b, a2) > b_arg;
}
template <class T>
Vec2<T> intersection(const Vec2<T> &a1, const Vec2<T> &a2, const Vec2<T> &b1, const Vec2<T> &b2) {
    static constexpr Vec2<T> error_val = {-2022, -2022};
    if (intersect_type(a1, a2, b1, b2) != 1) return error_val;
    return a1 + (a2 - a1) * (b1 - a1).cross(b2 - b1) / (a2 - a1).cross(b2 - b1);
}
template <class T>
double dis(const Vec2<T> &a, const Vec2<T> &b, const Vec2<T> &p) {
    return abs((p - a).cross(b - a) / (b - a).len());
}
template <class T>
double area_triangle(const Vec2<T> &a, const Vec2<T> &b) { return a.cross(b) / 2; }
template <class T>
long double area_polygon(const vector<Vec2<T>> &p) {
    long double area = 0;
    int sz = p.size();
    for (int i = 0; i < sz; i++) area += (long double)p[i].cross(p[(i + 1) % sz]) / 2;
    return area;
}
template <class T>
Vec2<T> center_of_grav_polygon(const vector<Vec2<T>> &p) {
    int n = p.size();
    Vec2<T> grav(0, 0);
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        grav += (p[i] + p[j]) * p[i].cross(p[j]);
    }
    return grav / (area_polygon(p) * 3);
}
template <class T>
vector<Vec2<T>> convex_hull(vector<Vec2<T>> &pts) {
    int n = pts.size();
    sort(pts.begin(), pts.end());
    stack<pair<int, int>> conv_idx;
    conv_idx.emplace(0, 1);
    for (int i = 2; i < n; i++) {
        int i1, i2;
        while (true) {
            i1 = conv_idx.top().first, i2 = conv_idx.top().second;
            if (inter_seg_pt(pts[i1], pts[i2], pts[i]) != 1) break;
            conv_idx.pop();
            if (conv_idx.empty()) {
                i2 = i1;
                break;
            }
        }
        conv_idx.emplace(i2, i);
    }
    for (int i = n - 2; i >= 0; i--) {
        int i1, i2;
        while (true) {
            i1 = conv_idx.top().first, i2 = conv_idx.top().second;
            if (inter_seg_pt(pts[i1], pts[i2], pts[i]) != 1) break;
            conv_idx.pop();
            if (conv_idx.empty()) {
                i2 = i1;
                break;
            }
        }
        conv_idx.emplace(i2, i);
    }
    int i = 0;
    vector<Vec2<T>> conv(conv_idx.size());
    while (conv_idx.size()) {
        conv[i++] = pts[conv_idx.top().first];
        conv_idx.pop();
    }
    return conv;
}

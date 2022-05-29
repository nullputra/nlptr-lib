namespace chinese_remainder_theorem {
using ll = long long;
constexpr pair<ll, ll> no_sol = {0, -1};
ll mod(ll x, ll y) { return x %= y, x < 0 ? x + y : x; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll g = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
pair<ll, ll> crt_2d(ll b1, ll m1, ll b2, ll m2) {
    ll p, q, g = ext_gcd(m1, m2, p, q);
    if ((b2 - b1) % g) return no_sol;
    ll lcm_m = m1 * (m2 / g);
    ll mul = (b2 - b1) / g * p % (m2 / g);
    ll r = mod(b1 + m1 * mul, lcm_m);
    return {r, lcm_m};
}
pair<ll, ll> crt(vector<ll> &b, vector<ll> &m) {
    assert(b.size() == m.size());
    ll r = 0, lcm_m = 1;
    for (int i = 0; i < (int)b.size(); i++) {
        ll p, q, g = ext_gcd(lcm_m, m[i], p, q);
        if ((b[i] - r) % g) return no_sol;
        ll mul = (b[i] - r) / g * p % (m[i] / g);
        r += lcm_m * mul;
        lcm_m *= m[i] / g;
    }
    return {mod(r, lcm_m), lcm_m};
}
}  // namespace chinese_remainder_theorem
using namespace chinese_remainder_theorem;

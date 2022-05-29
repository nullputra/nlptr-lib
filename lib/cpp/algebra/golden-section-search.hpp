template <class T>
pair<T, T> golden_section_search(T l_lim, T r_lim, const function<T(T)> &f, bool is_convex_upward) {
    assert(is_floating_point_v<T>);
    static constexpr T phi = (1 + sqrtl(5)) / 2, TINF = numeric_limits<T>::max();
    T l = l_lim, l2 = TINF, r2 = TINF, r = r_lim, f_l2 = TINF, f_r2 = TINF;
    using Comp = function<bool(T, T)>;
    const Comp comp = is_convex_upward ? (Comp)less<T>() : (Comp)greater<T>();
    while (l + 1e-10 < r) {
        if (l2 == TINF) l2 = (l * phi + r) / (phi + 1), f_l2 = f(l2);
        if (r2 == TINF) r2 = (l + r * phi) / (phi + 1), f_r2 = f(r2);
        if (comp(f_l2, f_r2)) {
            l = l2, l2 = r2, r2 = TINF, f_l2 = f_r2;
        } else {
            r = r2, r2 = l2, l2 = TINF, f_r2 = f_l2;
        }
    }
    if (f_r2 == TINF) f_r2 = f(r);
    return {r, f_r2};
}

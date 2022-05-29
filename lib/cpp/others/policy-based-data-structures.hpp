#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <class T, class Comp = less<T>>
using rb_set = tree<T, null_type, Comp, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash {
    static ulong splitmix64(ulong x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(ulong x) const {
        static const ulong FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<int, int> x) const {
        return operator()(ulong(x.first) << 32 | x.second);
    }
};
template <class T, class U>
using hash_table = gp_hash_table<T, U, custom_hash>;

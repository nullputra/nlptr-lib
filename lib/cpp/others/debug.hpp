#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <assert.h>
#include <math.h>
#include <atcoder/modint>
#include <chrono>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// [isdbg]
#ifdef _DEBUG
const bool isdbg = true;
#else
const bool isdbg = false;
#endif

// [to_string extender]
namespace std {

// std::string, const char*, char
template <class T>
string to_string(T x) {
    stringstream ss;
    ss << x;
    string res;
    getline(ss, res);
    return "\033[1;33m" + res + "\033[m";
}

// atcoder::static_modint<m>
template <int m>
string to_string(atcoder::static_modint<m> x) {
    return to_string(x.val());
}

// __int128_t
string to_string(__int128_t x) {
    static const string digs = "0123456789";
    string s;
    __uint128_t _x = x < 0 ? -x : x;
    do {
        s = digs[_x % 10] + s;
    } while (_x /= 10);
    if (x < 0) s = "-" + s;
    return s;
}

// internal_brackets_parse()
template <class T>
string to_string(vector<T> v) { return internal_brackets_parse(v, "[]"); }
template <class T, ulong n>
string to_string(array<T, n> a) { return internal_brackets_parse(a); }
template <class T>
string to_string(set<T> st) { return internal_brackets_parse(st); }
template <class K, class V>
string to_string(map<K, V> mp) { return internal_brackets_parse(mp); }
template <class K, class V>
string to_string(unordered_map<K, V> mp) { return internal_brackets_parse(mp); }
template <class T>
string to_string(deque<T> q) { return internal_brackets_parse(q); }

template <class A>
string internal_brackets_parse(A v, string brs = "{}") {
    assert(v.size() < 4096);  // avoid segfault
    string res;
    for (auto x : v) res += to_string(x) + ", ";
    return brs[0] + res.substr(0, res.size() - 2) + brs[1];
}

// std::priority_queue, std::queue, std::stack
template <class T, class Comp>
string to_string(priority_queue<T, vector<T>, Comp> q) {
    string res;
    while (!q.empty()) res = to_string(q.top()) + ", " + res, q.pop();
    return "heapq(" + res.substr(0, res.size() - 2) + ")";
}
template <class T>
string to_string(queue<T> q) {
    string res;
    while (!q.empty()) res = to_string(q.front()) + ", " + res, q.pop();
    return "queue(" + res.substr(0, res.size() - 2) + ")";
}
template <class T>
string to_string(stack<T> st) {
    string res;
    while (!st.empty()) res = to_string(st.top()) + ", " + res, st.pop();
    return "stack(" + res.substr(0, res.size() - 2) + ")";
}

// std::pair
template <class S, class T>
string to_string(pair<S, T> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

// std::tuple
// Ref: https://theolizer.com/cpp-school2/cpp-school2-20/
template <class Tuple, size_t... I>
string internal_tuple_parse(Tuple t, index_sequence<I...>) {
    string res;
    using swallow = int[];
    (void)swallow{(res += to_string(get<I>(t)) + ", ", 0)...};
    return "(" + res.substr(0, res.size() - 2) + ")";
}
template <class... Args>
string to_string(tuple<Args...> t) {
    constexpr size_t n = tuple_size<tuple<Args...>>::value;
    return internal_tuple_parse(t, make_index_sequence<n>{});
}

}  // namespace std

template <class T>
std::vector<T> internal_make_v(T *a, int n) {
    std::vector<T> res(n);
    for (int i = 0; i < n; i++) res[i] = a[i];
    return res;
}
#define make_v(a) internal_make_v(a, sizeof(a) / sizeof(a[0]))

template <class T>
std::vector<std::vector<T>> internal_make_vv(T *a, int h, int w) {
    std::vector<std::vector<T>> res(h, std::vector<T>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) res[i][j] = a[i * w + j];
    }
    return res;
}
#define make_vv(a) internal_make_vv(*a, sizeof(a) / sizeof(a[0]), sizeof(a[0]) / sizeof(a[0][0]))

// [dbg]
namespace dbg {

// dout
// Ref: https://ez-net.jp/article/0B/ydQ-Mn1E/uoSm36x6y4XR/
struct DbgOstream {
   private:
    bool is_first_arg;
    int trim_comma_max, trimed_comma_num;

   public:
    DbgOstream() { init(); }

    template <class T>
    friend DbgOstream &operator<<(DbgOstream &os, T x) {
        os.print_info();
        std::cerr << std::to_string(x);
        return os;
    }
    // dbg::endl
    // Ref: std::basic_ostream
    DbgOstream &operator<<(DbgOstream &(*pf)(DbgOstream &)) {
        return pf(*this);
    }

    void init() {
        is_first_arg = true;
        trim_comma_max = 1;
        trimed_comma_num = 0;
    }

   private:
    void print_info() {
        if (is_first_arg) {
            is_first_arg = false;
        } else {
            if (trimed_comma_num >= trim_comma_max) {
                std::cerr << ", ";
            } else {
                trimed_comma_num++;
            }
        }
    }
};
// dbg::endl
DbgOstream &endl(DbgOstream &os) {
    std::cerr << std::endl;
    os.init();
    return os;
}
DbgOstream _dout;

}  // namespace dbg

// dbg::_dout
#ifdef _DEBUG
#define dout std::cerr << "(\033[1;34m" << __LINE__ << "\033[m) ", dbg::_dout
#else
#define dout assert(std::string(__FILE__).find(".test") == std::string::npos), \
             std::cerr << "(\033[1;34m" << __LINE__ << "\033[m) ", dbg::_dout
#endif

// [tests]
struct TestsFortmatVerifier {
    TestsFortmatVerifier() {
        assert((std::string(__FILE__).find(".test") == std::string::npos) ^
               (std::string(__FILE__).find("tests/") != std::string::npos));
    }
} _TestsFortmatVerifier;

// [chrono]
// flag: 0. nano(ns), 1. micro(micros), 2. milli(ms)
// is_acc: 0. 1ms 2ms 3ms 4ms... , 1. 1ms 1ms 1ms 1ms...
void chro(int flag = -1, bool is_acc = true) {
    using namespace std::chrono;
    static int _flag = -1;
    static bool _is_acc = true;  // (_is_acc ? 累積差 : 経過時間) として表示する
    static system_clock::time_point prev_cnt;

    system_clock::time_point cnt = system_clock::now();
    if (!is_acc) _is_acc = is_acc;
    if (flag != -1) {
        _flag = flag;
    } else {  // 0.nano[ns] 1.micro[micros] 2.milli[ms]
        double time;
        switch (_flag) {
            case 0:
                time = duration_cast<nanoseconds>(cnt - prev_cnt).count();
                dout << time << " ns" << dbg::endl;
                break;
            case 1:
                time = duration_cast<microseconds>(cnt - prev_cnt).count();
                dout << time << " mcrs" << dbg::endl;
                break;
            case 2:
                time = duration_cast<milliseconds>(cnt - prev_cnt).count();
                dout << time << " ms" << dbg::endl;
                break;
        }
    }
    if (flag != -1 || _is_acc) prev_cnt = cnt;
}

#endif  // DEBUG_HPP

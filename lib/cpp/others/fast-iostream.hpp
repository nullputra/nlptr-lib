struct FastIstream {
    FastIstream() { cin.tie(nullptr), ios::sync_with_stdio(false); }
    void tie(ostream *) {}
    template <class T>
    friend enable_if_t<is_integral_v<T>, FastIstream> &operator>>(FastIstream &os, T &x) {
        bool f = false;
        int c = getchar();
        while (isspace(c)) c = getchar();
        if (c == '-') f = true, c = getchar();
        x = 0;
        for (; isdigit(c); c = getchar()) x = x * 10 + (c - '0');
        if (f) x = -x;
        return os;
    }
    template <class T>
    friend enable_if_t<!is_integral_v<T>, FastIstream> &operator>>(FastIstream &os, T &x) {
        cin >> x;
        return os;
    }
} _cin;
#define cin _cin
struct FastOstream {
    template <class T>
    friend enable_if_t<is_integral_v<T>, FastOstream> &operator<<(FastOstream &os, T x) {
        static char buf[20];
        if (x < 0) putchar('-'), x = -x;
        int len = 0;
        for (; !len || x; x /= 10) buf[len++] = x % 10 + '0';
        while (len) putchar(buf[--len]);
        return os;
    }
    friend FastOstream &operator<<(FastOstream &os, char x) {
        putchar(x);
        return os;
    }
    template <class T>
    friend enable_if_t<!is_integral_v<T>, FastOstream> &operator<<(FastOstream &os, const T &x) {
        cout << x;
        return os;
    }
} _cout;
#define cout _cout

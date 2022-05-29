template <class T, bool is_rect_addition>
struct CumulativeSum2d {
   private:
    int _h, _w;
    vector<vector<T>> v;
    bool built = false;

   public:
    CumulativeSum2d(int h, int w) : _h(h + 1), _w(w + 1) { init(); }
    void init() { v = vector(_h, vector<T>(_w)); }
    void add(int y1, int x1, int y2, int x2, T a) {
        assert(is_rect_addition && !built && 0 <= y1 && y1 <= y2 && y2 < _h && 0 <= x1 && x1 <= x2 && x2 < _w);
        y1++, x1++, y2++, x2++;
        v[y1][x1] += a, v[y1][x2] -= a, v[y2][x1] -= a, v[y2][x2] += a;
    }
    T get(int y, int x) {
        assert(is_rect_addition && 0 <= y && y < _h && 0 <= x && x < _w);
        build();
        return v[y + 1][x + 1];
    }
    void add(int y, int x, T a) {
        assert(!is_rect_addition && !built && 0 <= y && y < _h && 0 <= x && x < _w);
        v[y + 1][x + 1] += a;
    }
    T get(int y1, int x1, int y2, int x2) {
        assert(!is_rect_addition && 0 <= y1 && y1 <= y2 && y2 < _h && 0 <= x1 && x1 <= x2 && x2 < _w);
        build();
        return v[y2][x2] - v[y1][x2] - v[y2][x1] + v[y1][x1];
    }
#ifdef _DEBUG
    void print(bool prints_prev = true) {
        auto _print = [&]() {
            for (int i = 1; i < _h; i++) {
                for (int j = 1; j < _w; j++) {
                    if (j > 1) cout << ' ';
                    cout << v[i][j];
                }
                cout << '\n';
            }
            cout << '\n';
        };
        if (!built && prints_prev) _print();
        build();
        _print();
    }
#else
    void print(bool = true) {}
#endif

   private:
    void build() {
        if (built) return;
        built = true;
        for (int i = 1; i < _h; i++) {
            for (int j = 1; j < _w; j++) v[i][j] += v[i - 1][j];
        }
        for (int i = 1; i < _h; i++) {
            for (int j = 1; j < _w; j++) v[i][j] += v[i][j - 1];
        }
    }
};

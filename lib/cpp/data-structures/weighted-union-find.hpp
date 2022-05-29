template <class T>
struct WeightedUnionFind {
   private:
    int _n;
    vector<int> par;
    vector<T> wts;

   public:
    WeightedUnionFind(int n, T id = 0) : _n(n), par(_n, -1), wts(_n, id) {}
    bool merge(int x, int y, T w) {
        assert(0 <= x && x < _n && 0 <= y && y < _n);
        w += weight(x) - weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y), w = -w;
        par[x] += par[y], par[y] = x, wts[y] += w;
        return true;
    }
    int find(int x) {
        assert(0 <= x && x < _n);
        if (par[x] < 0) return x;
        int par_x = find(par[x]);
        wts[x] += wts[par[x]];
        return par[x] = par_x;
    }
    T weight(int x) {
        assert(0 <= x && x < _n);
        find(x);
        return wts[x];
    }
    T diff(int x, int y) {
        assert(0 <= x && x < _n && 0 <= y && y < _n);
        return weight(y) - weight(x);
    }
    bool same(int x, int y) {
        assert(0 <= x && x < _n && 0 <= y && y < _n);
        return find(x) == find(y);
    }
    int size(int x) {
        assert(0 <= x && x < _n);
        return -par[find(x)];
    }
};

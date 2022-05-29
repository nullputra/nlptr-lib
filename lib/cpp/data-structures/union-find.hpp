struct UnionFind {
   private:
    int _n;
    vector<int> par;

   public:
    UnionFind(int n) : _n(n), par(_n, -1) {}
    bool merge(int x, int y) {
        assert(0 <= x && x < _n && 0 <= y && y < _n);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y], par[y] = x;
        return true;
    }
    int find(int x) {
        assert(0 <= x && x < _n);
        return par[x] < 0 ? x : par[x] = find(par[x]);
    }
    bool same(int x, int y) {
        assert(0 <= x && x < _n && 0 <= y && y < _n);
        return find(x) == find(y);
    }
    int size(int x) {
        assert(0 <= x && x < _n);
        return -par[find(x)];
    }
    vector<vector<int>> groups() {
        vector<int> _find(_n), _size(_n);
        for (int i = 0; i < _n; i++) _find[i] = find(i), _size[_find[i]]++;
        vector<vector<int>> res(_n);
        for (int i = 0; i < _n; i++) res[i].reserve(_size[i]);
        for (int i = 0; i < _n; i++) res[_find[i]].push_back(i);
        res.erase(remove_if(res.begin(), res.end(), [](vector<int> &v) { return v.empty(); }), res.end());
        return res;
    }
};

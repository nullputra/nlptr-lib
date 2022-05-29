struct SA_IS {
   private:
    string _s;
    int _low_ch, _high_ch;
    vector<int> sa, cnt;

   public:
    SA_IS(const string &s, int low_ch = '0', int high_ch = 'z')
        : _s(s), _low_ch(low_ch), _high_ch(high_ch) {}
    vector<int> get_sa() {
        if (sa.size()) return sa;
        int n = _s.size();
        vector<int> vs(n);
        for (int i = 0; i < n; i++) vs[i] = _s[i] - _low_ch;
        return sa_is(vs, _high_ch - _low_ch + 1);
    }
    bool contains(const string &t, bool is_prefix_match = false) {
        if (sa.empty()) get_sa();
        int ng = -1, ok = _s.size();
        while (ok - ng > 1) {
            int mid = (ok + ng) / 2;
            (_s.compare(sa[mid], t.size(), t) >= 0 ? ok : ng) = mid;
        }
        return is_prefix_match ? true : !_s.compare(sa[ok], t.size(), t);
    }
    void print() {
        int n = _s.size(), dig = log10(n) + 1;
        for (int i = 0; i <= n; i++) {
            cout << "_s[" << setw(dig) << sa[i] << ":] = " << _s.substr(sa[i]) << '\n';
        }
    }

   private:
    vector<int> &sa_is(vector<int> s1, int sz) {
        int n = s1.size();
        sa.resize(n + 1);
        if (n == 0) return sa;
        for (auto &c : s1) c++;
        s1.push_back(0);
        sz++;
        vector<bool> iss(n + 1);
        vector<int> bin(sz + 1);
        auto induce = [&](const vector<int> &lms) {
            sa.assign(n + 1, -1);
            cnt.assign(sz, 0);
            for (int i = 0; i < (int)lms.size(); i++) {
                int sx = s1[lms[i]];
                sa[bin[sx + 1] - 1 - cnt[sx]++] = lms[i];
            }
            cnt.assign(sz, 0);
            for (int i = 0; i <= n; i++) {
                int x = sa[i] - 1;
                if (x >= 0 && !iss[x]) sa[bin[s1[x]] + cnt[s1[x]]++] = x;
            }
            cnt.assign(sz, 0);
            for (int i = n; i >= 0; i--) {
                int x = sa[i] - 1;
                if (x >= 0 && iss[x]) sa[bin[s1[x] + 1] - 1 - cnt[s1[x]]++] = x;
            }
        };
        vector<int> lms, lms_sz(n + 1, -1);
        iss[n] = 1, bin[1]++;
        for (int i = n - 1; i >= 0; i--) {
            iss[i] = s1[i] == s1[i + 1] ? iss[i + 1] : s1[i] < s1[i + 1];
            if (!iss[i] && iss[i + 1]) {
                lms_sz[i + 1] = lms.size();
                lms.push_back(i + 1);
            }
            bin[s1[i] + 1]++;
        }
        for (int i = 0; i < sz; i++) bin[i + 1] += bin[i];
        induce(lms);
        if (lms.size() > 1) {
            int m = lms.size(), li = 0;
            vector<int> sorted_lms(m);
            for (auto x : sa) {
                if (lms_sz[x] != -1) sorted_lms[li++] = x;
            }
            int n2 = 1;
            vector<int> s2(m);
            s2[m - 1 - lms_sz[sorted_lms[1]]] = 1;
            for (int i = 2; i < m; i++) {
                int xl = sorted_lms[i], yl = sorted_lms[i - 1];
                int xr = lms[lms_sz[xl] - 1], yr = lms[lms_sz[yl] - 1];
                if (xr - xl != yr - yl) {
                    n2++;
                } else {
                    while (xl <= xr) {
                        if (s1[xl] != s1[yl]) {
                            n2++;
                            break;
                        }
                        xl++, yl++;
                    }
                }
                s2[m - 1 - lms_sz[sorted_lms[i]]] = n2;
            }
            vector<int> lms_sa = sa_is(move(s2), n2 + 1);
            li = m;
            for (int i = 1; i <= m; i++) sorted_lms[--li] = lms[m - 1 - lms_sa[i]];
            induce(sorted_lms);
        }
        return sa;
    }
};

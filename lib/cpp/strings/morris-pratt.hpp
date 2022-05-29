vector<int> morris_pratt(const string &s, bool is_knuth = false) {
    int n = s.size(), j = -1;
    vector<int> b(n + 1);
    b[0] = -1;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && s[i] != s[j]) j = b[j];
        b[i + 1] = is_knuth ? (s[i + 1] == s[++j] ? b[j] : j) : ++j;
    }
    return b;
}

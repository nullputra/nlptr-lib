vector<int> manacher(const string &s) {
    int n = s.size(), i = 0, len = 0;
    vector<int> r(n);
    while (i < n) {
        while (i - len >= 0 && i + len < n && s[i - len] == s[i + len]) len++;
        r[i] = len;
        int reused_len = 1;
        while (i - reused_len >= 0 && reused_len + r[i - reused_len] < len) {
            r[i + reused_len] = r[i - reused_len], reused_len++;
        }
        i += reused_len, len -= reused_len;
    }
    return r;
}

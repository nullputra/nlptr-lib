vector<int> z_algorithm(string &s, int x = 0) {
    int n = s.size() - x;
    vector<int> z(n);
    z[0] = n;
    for (int i = 1, len = 0; i < n;) {
        while (i + len < n && s[x + len] == s[x + i + len]) len++;
        z[i] = len;
        if (len == 0) {
            i++;
            continue;
        }
        int reused_len = 1;
        while (reused_len + z[reused_len] < len) {
            z[i + reused_len] = z[reused_len], reused_len++;
        }
        i += reused_len, len -= reused_len;
    }
    return z;
}
vector<int> z_search(const string &s, const string &ptn) {
    string t = ptn + "$" + s;
    int nt = s.size(), np = ptn.size();
    vector<int> z_idx, z = z_algorithm(t);
    for (int i = np + 1; i < nt + 2; i++) {
        if (z[i] == np) z_idx.push_back(i - np - 1);
    }
    return z_idx;
}

template <class W>
struct Trie {
   private:
    struct Node {
        char ch;
        W w;
        int nxt, bro;
    };
    vector<Node> nodes;

   public:
    Trie() : nodes(1, {-1, W(), -1, -1}) {}
    void insert(string &s, W s_w) {
        int cur = 0;
        for (char &ch : s) {
            bool upd = false;
            if (nodes[cur].nxt >= 0) {
                for (int b = cur; b >= 0; b = nodes[b].bro) {
                    if (ch == nodes[b].ch) {
                        cur = nodes[b].nxt, upd = true;
                        break;
                    }
                }
            }
            if (upd) continue;
            if (nodes[cur].nxt > 0) {
                nodes.push_back({ch, W(), (int)nodes.size() + 1, nodes[cur].bro});
                nodes[cur].bro = nodes.size() - 1;
            } else {
                nodes[cur].nxt = nodes.size(), nodes[cur].ch = ch;
            }
            cur = nodes.size();
            nodes.push_back({-1, W(), -1, -1});
        }
        nodes[cur].w = s_w;
    }
    void find(string &t, const function<void(int t_r, W w)> &f, int s_l = 0, int t_l = 0) {
        int n = t.size(), cur = s_l;
        assert(s_l < (int)nodes.size() && t_l < n);
        for (int t_r = t_l; t_r < n; t_r++) {
            bool upd = false;
            if (nodes[cur].nxt >= 0) {
                for (int b = cur; b >= 0; b = nodes[b].bro) {
                    if (t[t_r] == nodes[b].ch) {
                        cur = nodes[b].nxt, upd = true;
                        break;
                    }
                }
            }
            if (!upd) return;
            if (nodes[cur].ch == -1) f(t_r, nodes[cur].w);
        }
    }
#ifdef _DEBUG
    void print(int cur = 0) {
        static string u;
        if (!cur) cout << "print():\n", u.clear();
        if (nodes[cur].ch == -1) {
            cout << setw(4) << u;
            if (is_arithmetic_v<W>) cout << setw(4) << nodes[cur].w;
            cout << '\n';
        }
        u.push_back(0);
        if (nodes[cur].nxt >= 0) {
            for (int b = cur; b >= 0; b = nodes[b].bro) {
                u.back() = nodes[b].ch;
                print(nodes[b].nxt);
            }
        }
        u.pop_back();
    }
#else
    void print() {}
#endif
};

template <class T>
struct Zip : vector<T> {
   public:
    vector<T> uniq;

   private:
    int _n;
    bool built = false;

   public:
    Zip() : _n(0) {}
    Zip(int n) : _n(n) { this->resize(_n); }
    void build() {
        if (built) return;
        built = true;
        uniq = *this;
        sort(uniq.begin(), uniq.end());
        uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
        for (int i = 0; i < _n; i++) {
            (*this)[i] = lower_bound(uniq.begin(), uniq.end(), (*this)[i]) - uniq.begin();
        }
    }
    void push_back(T x) { assert(!built), this->push_back(x), _n++; }
    int val_to_ind(T x) { return build(), lower_bound(uniq.begin(), uniq.end(), x) - uniq.begin(); }
    int size() { return build(), uniq.size(); }
    void print() {
        build();
        cout << "z: [";
        for (int i = 0; i < _n; i++) {
            if (i) cout << ", ";
            cout << "(" << (*this)[i] << ", " << uniq[(*this)[i]] << ")";
        }
        cout << "]\n";
    }
};

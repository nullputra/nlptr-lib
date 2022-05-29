# Ref: https://atcoder.jp/contests/abc248/submissions/31017251, unidayo
class SegmentTree:
    def __init__(self, op, e, n=0, *, array=None):
        assert (n > 0 and array is None) or (n == 0 and array)
        self.e = e
        self.op = op
        self.n = n if n else len(array)
        self.log = (self.n - 1).bit_length()
        self.size = 1 << self.log
        self.d = [e] * (2 * self.size)

        if array:
            for i in range(self.n):
                self.d[self.size + i] = array[i]
            for i in reversed(range(1, self.size)):
                self.__update(i)

    def set(self, p, x):
        """a[p] に x を代入する"""
        p += self.size
        self.d[p] = x
        for i in range(1, self.log + 1):
            self.__update(p >> i)

    def get(self, p):
        """a[p]を返す"""
        return self.d[p + self.size]

    def prod(self, l, r):
        """[l, r) の総積を返す"""
        if l == 0 and r >= self.n:
            return self.all_prod()

        op = self.op

        sml = self.e
        smr = self.e

        l += self.size
        r += self.size

        while l < r:
            if l & 1:
                sml = op(sml, self.d[l])
                l += 1
            if r & 1:
                r -= 1
                smr = op(self.d[r], smr)
            l >>= 1
            r >>= 1
        return op(sml, smr)

    def all_prod(self):
        """[0, n) の総積を返す"""
        return self.d[1]

    def max_right(self, l, f):
        """f(op(a[l:r])) == True となる最大のr（fが単調ならば）"""
        if l == self.n:
            return self.n
        op = self.op
        size = self.size
        l += size
        sm = self.e

        while True:
            while not (l & 1):
                l >>= 1
            if not f(op(sm, self.d[l])):
                while l < size:
                    l <<= 1
                    if f(op(sm, self.d[l])):
                        sm = op(sm, self.d[l])
                        l += 1
                return l - size
            sm = op(sm, self.d[l])
            l += 1
            if (l & -l) == l:
                break
        return self.n

    def min_left(self, r, f):
        """f(op(a[l:r])) == True となる最小のl（fが単調ならば）"""
        if r == 0:
            return 0
        op = self.op
        size = self.size
        r += self.size
        sm = self.e

        while True:
            r -= 1
            while r and r & 1:
                r >>= 1
            if not f(op(self.d[r], sm)):
                while r < size:
                    r = 2 * r + 1
                    if f(op(self.d[r], sm)):
                        sm = op(self.d[r], sm)
                        r -= 1
                return r + 1 - size
            sm = op(self.d[r], sm)
            if (r & -r) == r:
                break
        return 0

    def __update(self, k):
        self.d[k] = self.op(self.d[k << 1], self.d[k << 1 | 1])

    def __getitem__(self, key):
        if isinstance(key, slice):
            start, stop = key.start, key.stop
            if start is None:
                start = 0
            if stop is None:
                stop = self.n
            return self.prod(start, stop)
        else:
            return self.d[key + self.size]

    def __setitem__(self, key, value):
        self.set(key, value)

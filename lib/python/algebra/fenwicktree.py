# Ref: not522/ac-library-python https://github.com/not522/ac-library-python/blob/master/atcoder/fenwicktree.py
class FenwickTree:
    def __init__(self, n=0):
        self._n = n
        self.data = [0] * n

    def add(self, p, x):
        assert 0 <= p < self._n
        p += 1
        while p <= self._n:
            self.data[p - 1] += x
            p += p & -p

    def sum(self, l, r):
        assert 0 <= l <= r <= self._n
        return self._sum(r) - self._sum(l)

    def _sum(self, r):
        res = 0
        while r > 0:
            res += self.data[r - 1]
            r -= r & -r
        return res

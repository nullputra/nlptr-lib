# Ref: not522/ac-library-python https://github.com/not522/ac-library-python/blob/master/atcoder/dsu.py
class UnionFind:
    def __init__(self, n=0):
        self._n = n
        self.parent_or_size = [-1] * n

    def merge(self, a, b):
        assert 0 <= a < self._n
        assert 0 <= b < self._n
        x = self.find(a)
        y = self.find(b)
        if x == y:
            return x
        if -self.parent_or_size[x] < -self.parent_or_size[y]:
            x, y = y, x
        self.parent_or_size[x] += self.parent_or_size[y]
        self.parent_or_size[y] = x
        return x

    def same(self, a, b):
        assert 0 <= a < self._n
        assert 0 <= b < self._n
        return self.find(a) == self.find(b)

    def find(self, a):
        assert 0 <= a < self._n
        parent = self.parent_or_size[a]
        while parent >= 0:
            if self.parent_or_size[parent] < 0:
                return parent
            self.parent_or_size[a], a, parent = (
                self.parent_or_size[parent],
                self.parent_or_size[parent],
                self.parent_or_size[self.parent_or_size[parent]],
            )
        return a

    def size(self, a):
        assert 0 <= a < self._n
        return -self.parent_or_size[self.find(a)]

    def groups(self):
        leader_buf = [self.find(i) for i in range(self._n)]
        result = [[] for _ in range(self._n)]
        for i in range(self._n):
            result[leader_buf[i]].append(i)
        return list(filter(lambda r: r, result))

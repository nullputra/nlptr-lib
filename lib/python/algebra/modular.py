MOD = 998244353


class Modular:
    def __init__(self, v=0):
        self._v = 0 if v == 0 else v % MOD

    def init_unchecked(self, v):
        x = Modular()
        x._v = v
        return x

    def val(self):
        return self._v

    def __iadd__(self, rhs):
        self._v += rhs._v if isinstance(rhs, Modular) else rhs
        if self._v >= MOD:
            self._v -= MOD
        return self

    def __isub__(self, rhs):
        self._v -= rhs._v if isinstance(rhs, Modular) else rhs
        if self._v < 0:
            self._v += MOD
        return self

    def __imul__(self, rhs):
        self._v *= rhs._v if isinstance(rhs, Modular) else rhs
        self._v %= MOD
        return self

    def __ifloordiv__(self, rhs):
        inv = rhs.inv()._v if isinstance(rhs, Modular) else self.pow(rhs, MOD - 2)
        self._v = self._v * inv % MOD
        return self

    def __pos__(self):
        return self

    def __neg__(self):
        return Modular() - self

    def __pow__(self, n):
        assert n >= 0
        return self.init_unchecked(pow(self._v, n))

    def pow(self, n):
        assert n >= 0
        x = self._v
        res = self.init_unchecked(1)
        while n:
            if n & 1:
                res *= x
            x *= x
            n >>= 1
        return res

    def inv(self):
        return self.pow(self._v, MOD - 2)

    def __add__(self, rhs):
        if isinstance(rhs, Modular):
            res = self._v + rhs._v
            return self.init_unchecked(res - MOD if res >= MOD else res)
        else:
            return Modular(self._v + rhs)

    def __sub__(self, rhs):
        if isinstance(rhs, Modular):
            res = self._v - rhs._v
            return self.init_unchecked(res + MOD if res < 0 else res)
        else:
            return Modular(self._v - rhs)

    def __mul__(self, rhs):
        return Modular(self._v * (rhs._v if isinstance(rhs, Modular) else rhs))

    def __floordiv__(self, rhs):
        inv = rhs.inv()._v if isinstance(rhs, Modular) else self.pow(rhs, MOD - 2)
        return Modular(self._v * inv)

    def __eq__(self, rhs):
        return self._v == (rhs._v if isinstance(rhs, Modular) else rhs)

    def __ne__(self, rhs):
        return self._v != (rhs._v if isinstance(rhs, Modular) else rhs)

    def __repr__(self):
        return str(self._v)

mr = Modular

// Ref: https://github.com/camypaper/complib/blob/master/Library/Collections/Fenwick.cs
using System.Diagnostics;

// i, j は 全て 1-indexed です.
namespace Lib.FenwickTree
{
    public class FenwickTree
    {
        int n;
        long[] bit;
        int kMax = 1;
        public FenwickTree(int n)
        {
            this.n = n; bit = new long[n + 1];
            while ((kMax << 1) <= n) kMax <<= 1;
        }
        // Sum of [1, i].
        public long this[int i]
        {
            get
            {
                Debug.Assert(0 <= i && i <= n);
                if (i == 0) return 0;
                long sum = 0;
                for (; i > 0; i -= i & -i) sum += bit[i];
                return sum;
            }
        }
        public long this[int i, int j]
        {
            get
            {
                Debug.Assert(0 <= i && i <= j && j <= n);
                return i == 0 ? this[j] : this[j] - this[i - 1];
            }
        }
        public int LowerBound(long w)
        {
            if (w <= 0) return 0;
            int x = 0;
            for (int k = kMax; k > 0; k >>= 1)
            {
                if (x + k <= n && bit[x + k] < w)
                {
                    w -= bit[x + k];
                    x += k;
                }
            }
            return x + 1;
        }
        public void Add(int i, long x)
        {
            Debug.Assert(1 <= i && i <= n);
            for (; i < bit.Length; i += i & -i) bit[i] += x;
        }
        public long[] Items
        {
            get
            {
                var res = new long[n + 1];
                for (int i = 0; i < res.Length; i++) res[i] = this[i, i];
                return res;
            }
        }
    }
    public class RangeAddFenwickTree
    {
        int n;
        FenwickTree a, b;
        public RangeAddFenwickTree(int n)
        {
            this.n = n;
            a = new FenwickTree(n + 1);
            b = new FenwickTree(n + 1);
        }
        public void Add(int i, int j, long x)
        {
            Debug.Assert(1 <= i && i <= j && j <= n);
            a.Add(i, -(i - 1) * x);
            a.Add(j + 1, j * x);
            b.Add(i, x);
            b.Add(j + 1, -x);
        }
        // Sum of [1, i].
        public long this[int i]
        {
            get
            {
                Debug.Assert(0 <= i && i <= n);
                return i == 0 ? 0 : a[i] + b[i] * i;
            }
        }
        // Sum of [i, j].
        public long this[int i, int j]
        {
            get
            {
                Debug.Assert(0 <= i && i <= j && j <= n);
                return i == 0 ? this[j] : this[j] - this[i - 1];
            }
        }
        public long[] Items
        {
            get
            {
                var res = new long[n + 1];
                for (int i = 0; i < res.Length; i++) res[i] = this[i, i];
                return res;
            }
        }
    }
}

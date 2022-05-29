// Ref: https://ei1333.github.io/library/structure/union-find/weighted-union-find.cpp
using System;
using System.Diagnostics;

namespace Lib.WeightedUnionFind
{
    public class WeightedUnionFind<T> where T : IEquatable<T>
    {
        int n;
        T id;
        Func<T, T, T> add;
        Func<T, T, T> sub;
        int[] par;
        T[] wts;
        public WeightedUnionFind(int n, Func<T, T, T> add, Func<T, T, T> sub, T id)
        {
            Debug.Assert(add(id, id).Equals(id));
            Debug.Assert(sub(id, id).Equals(id));
            this.n = n;
            this.add = add;
            this.sub = sub;
            this.id = id;
            par = new int[n];
            for (int i = 0; i < n; i++) par[i] = -1;
            wts = new T[n];
            for (int i = 0; i < n; i++) wts[i] = id;
        }
        public bool TryUnite(int x, int y, T w) =>
            Unite(x, y, w) || add(Weight(x), w).Equals(Weight(y));
        public bool Unite(int x, int y, T w)
        {
            Debug.Assert(0 <= x && x < n && 0 <= y && y < n);
            w = sub(add(w, Weight(x)), Weight(y));
            x = Find(x); y = Find(y);
            if (x == y) return false;
            if (-par[x] < -par[y])
            {
                (x, y) = (y, x);
                w = sub(id, w);
            }
            par[x] += par[y];
            par[y] = x;
            wts[y] = add(wts[y], w);
            return true;
        }
        public int Find(int x)
        {
            Debug.Assert(0 <= x && x < n);
            if (par[x] < 0) return x;
            int par_x = Find(par[x]);
            wts[x] = add(wts[x], wts[par[x]]);
            return par[x] = par_x;
        }
        public T Weight(int x)
        {
            Debug.Assert(0 <= x && x < n);
            int _ = Find(x);
            return wts[x];
        }
        public T Diff(int x, int y)
        {
            Debug.Assert(0 <= x && x < n && 0 <= y && y < n);
            return sub(Weight(x), Weight(y));
        }
        public bool Same(int x, int y)
        {
            Debug.Assert(0 <= x && x < n && 0 <= y && y < n);
            return Find(x) == Find(y);
        }
        public int Size(int x)
        {
            Debug.Assert(0 <= x && x < n);
            return -par[Find(x)];
        }
    }
}

// Ref: https://github.com/camypaper/complib/blob/master/Library/Collections/DisjointSet.cs
using System.Collections.Generic;
using System.Diagnostics;

namespace Lib.RollbackUnionFind
{
    public class RollbackUnionFind
    {
        int n;
        int[] par;
        Stack<int> his = new Stack<int>();
        public RollbackUnionFind(int n)
        {
            this.n = n;
            par = new int[n];
            for (int i = 0; i < n; i++) par[i] = -1;
        }
        public RollbackUnionFind(int n, int[] p, byte[] r)
        {
            this.n = n;
            par = new int[2 * n];
            for (int i = 0; i < n; i++)
            {
                par[i] = p[i];
                par[i + n] = r[i];
            }
        }
        public int this[int x]
        {
            get
            {
                Debug.Assert(0 <= x && x < n);
                return par[x] < 0 ? x : par[x] = this[par[x]];
            }
        }
        public bool Unite(int x, int y)
        {
            Debug.Assert(0 <= x && x < n && 0 <= y && y < n);
            x = this[x]; y = this[y];
            if (x == y) return false;
            if (par[x + n] < par[y + n]) { var z = x; x = y; y = z; }
            his.Push(par[x]);
            his.Push(x);
            his.Push(par[y]);
            his.Push(y);
            par[x] += par[y];
            par[y] = x;
            if (par[x + n] == par[y + n])
            {
                his.Push(par[x + n]);
                his.Push(x + n);
                par[x + n]++;
            }
            return true;
        }
        public void Back()
        {
            if (his.Count == 0) return;
            for (int t = his.Peek() >= n ? 3 : 2; t > 0; t--)
            {
                var v2 = his.Pop();
                var v1 = his.Pop();
                par[v2] = v1;
            }
        }
        public int Size(int x)
        {
            Debug.Assert(0 <= x && x < n);
            return -par[this[x]];
        }
        public bool Same(int x, int y)
        {
            Debug.Assert(0 <= x && x < n && 0 <= y && y < n);
            return this[x] == this[y];
        }

    }
}

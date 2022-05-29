using System.Diagnostics;

namespace Lib.UnionFind
{
    public class UnionFind
    {
        int n;
        int[] par;
        public UnionFind(int n)
        {
            this.n = n;
            par = new int[n];
            for (int i = 0; i < n; i++) par[i] = -1;
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
            if (-par[x] < -par[y]) (x, y) = (y, x);
            par[x] += par[y];
            par[y] = x;
            return true;
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

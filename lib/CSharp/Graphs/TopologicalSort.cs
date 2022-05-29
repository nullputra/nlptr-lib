using System.Collections.Generic;

namespace Lib
{
    class TopologicalSort
    {
        public static int[] TopoSort(List<int>[] edges) {
            var n = edges.Length;
            var cnt = new int[n];
            for (var u1 = 0; u1 < n; u1++)
            {
                foreach (var u2 in edges[u1]) cnt[u2]++;
            }
            var q = new Queue<int>();
            for (int v = 0; v < n; v++)
            {
                if (cnt[v] == 0) q.Enqueue(v);
            }
            var sorted = new int[n];
            var sortedIdx = 0;
            var v1 = -1;
            while (q.TryDequeue(out v1))
            {
                sorted[sortedIdx++] = v1;
                if (sortedIdx == n) return sorted;
                foreach (var v2 in edges[v1])
                {
                    if (--cnt[v2] == 0) q.Enqueue(v2);
                }
            }
            return new int[0];
        }
    }
}

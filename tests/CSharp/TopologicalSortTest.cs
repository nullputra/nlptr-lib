using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using static Lib.TopologicalSort;

class TopologicalSortTest
{
    static void Main()
    {
        // AOJ - Topological Sort https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B
        int n = 6, m = 6;
        var edges = Enumerable.Range(0, n).Select(i => new List<int>()).ToArray();
        var uv = new int[,] { { 0, 1 }, { 1, 2 }, { 3, 1 }, { 3, 4 }, { 4, 5 }, { 5, 2 } };
        for (int i = 0; i < m; i++)
        {
            int u = uv[i, 0], v = uv[i, 1];
            edges[u].Add(v);
        }
        var sorted = TopoSort(edges);
        var modelAns = new int[] { 0, 3, 1, 4, 5, 2 };
        for (int i = 0; i < sorted.Length; i++)
        {
            Debug.Assert(modelAns[i] == sorted[i]);
        }
    }
}

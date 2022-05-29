// Ref:
//   https://qiita.com/keymoon/items/2a52f1b0fb7ef67fb89e
//   https://github.com/key-moon/Library/blob/master/src/Algorithm/rerooting.csx
using System.Collections.Generic;
using System;

class Rerooting<T>
{
    public int n { get; private set; }
    int[][] edges;
    int[][] edgeIndices;
    public T[] res;
    T[][] dp;
    T id;
    Func<T, T, T> merge;
    Func<T, int, T> opNode;
    public Rerooting(int n, int[][] edgePaths, T id, Func<T, T, T> merge, Func<T, int, T> opNode)
    {
        this.n = n;
        this.id = id;
        this.merge = merge;
        this.opNode = opNode;
        List<int>[] edges = new List<int>[n];
        List<int>[] edgeIndices = new List<int>[n];
        for (int i = 0; i < n; i++)
        {
            edges[i] = new List<int>();
            edgeIndices[i] = new List<int>();
        }
        for (int i = 0; i < edgePaths.Length; i++)
        {
            var edge = edgePaths[i];
            edgeIndices[edge[0]].Add(edges[edge[1]].Count);
            edgeIndices[edge[1]].Add(edges[edge[0]].Count);
            edges[edge[0]].Add(edge[1]);
            edges[edge[1]].Add(edge[0]);
        }
        this.edges = new int[n][];
        this.edgeIndices = new int[n][];
        for (int i = 0; i < n; i++)
        {
            this.edges[i] = edges[i].ToArray();
            this.edgeIndices[i] = edgeIndices[i].ToArray();
        }
        dp = new T[edges.Length][];
        res = new T[edges.Length];
        for (int i = 0; i < edges.Length; i++) dp[i] = new T[edges[i].Count];
        if (n > 1) Initialize();
        else if (n == 1) res[0] = opNode(id, 0);
    }
    public T Query(int i) => res[i];
    private void Initialize()
    {
        int[] parents = new int[n];
        int[] order = new int[n];
        // InitOrderedTree
        var index = 0;
        Stack<int> stack = new Stack<int>();
        stack.Push(0);
        parents[0] = -1;
        while (stack.Count > 0)
        {
            var node = stack.Pop();
            order[index++] = node;
            for (int i = 0; i < edges[node].Length; i++)
            {
                var adjacent = edges[node][i];
                if (adjacent == parents[node]) continue;
                stack.Push(adjacent);
                parents[adjacent] = node;
            }
        }
        // fromLeaf
        for (int i = order.Length - 1; i >= 1; i--)
        {
            var node = order[i];
            var parent = parents[node];
            T accum = id;
            int parentIndex = -1;
            for (int j = 0; j < edges[node].Length; j++)
            {
                if (edges[node][j] == parent)
                {
                    parentIndex = j;
                    continue;
                }
                accum = merge(accum, dp[node][j]);
            }
            dp[parent][edgeIndices[node][parentIndex]] = opNode(accum, node);
        }
        // toLeaf
        for (int i = 0; i < order.Length; i++)
        {
            var node = order[i];
            T accum = id;
            T[] accumsFromTail = new T[edges[node].Length];
            accumsFromTail[accumsFromTail.Length - 1] = id;
            for (int j = accumsFromTail.Length - 1; j >= 1; j--) accumsFromTail[j - 1] = merge(dp[node][j], accumsFromTail[j]);
            for (int j = 0; j < accumsFromTail.Length; j++)
            {
                dp[edges[node][j]][edgeIndices[node][j]] = opNode(merge(accum, accumsFromTail[j]), node);
                accum = merge(accum, dp[node][j]);
            }
            res[node] = opNode(accum, node);
        }
    }
}

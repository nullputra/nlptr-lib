using System.Diagnostics;
using Lib.FenwickTree;

class FenwickTreeTest
{
    static void Main()
    {
        FenwickTreeWorks();
        RangeAddFenwickTreeWorks();
    }
    static void FenwickTreeWorks()
    {
        var n = 4;
        var a = new int[] { 1, 2, 3, 4 };
        // 実装の都合上, 0 番目に書き込み不可能な 0 を置いています.
        // 長さ n + 1 の数列として初期化.
        var ft = new FenwickTree(n);
        for (int i = 0; i < n; i++)
        {
            // 0 番目は書き込み不可能なので, 1 ~ n 番目しか Add 出来ません.
            ft.Add(i + 1, a[i]);
        }

        var modelAns = new int[] { 0, 1, 2, 3, 4 };
        for (int i = 0; i <= n; i++)
        {
            // ft[i, j]: 区間 [i, j] の和を返す.
            //           0 番目も読み取りできますが, 0 <= i <= j <= n である必要があります.
            Debug.Assert(modelAns[i] == ft[i, i]);
        }
    }
    static void RangeAddFenwickTreeWorks()
    {
        var n = 4;
        var a = new int[] { 1, 2, 3, 4 };
        var ft = new RangeAddFenwickTree(n);
        for (int i = 0; i < n; i++)
        {
            // ft.Add(i, j, x): 区間 [i, j] に x を加算.
            ft.Add(i + 1, n, a[i]);
        }

        var modelAns = new int[] { 0, 1, 3, 6, 10 };
        for (int i = 0; i <= n; i++)
        {
            Debug.Assert(modelAns[i] == ft[i, i]);
        }
    }
}

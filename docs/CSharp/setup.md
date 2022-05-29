# 🎯 C# の環境構築

## 1. WSL を入れます
- 参考: [lib/set-up-wsl](https://nullputra.github.io/nlptr-lib/set-up-wsl.html)


## 2. 初期設定

### A. `dotnet` のインストール
#### ターミナル
```sh
apt install -y dotnet-sdk-3.1
```

### B. ビルドや実行に必要なファイル群の自動生成
以下のコードを実行すると、カレントディレクトリ直下に `<PROJECT_NAME>` というディレクトリが作られ、そのディレクトリの中に `./<PROJECT_NAME>/<PROJECT_NAME>.csproj` などのビルドや実行に必要なファイル群が生成されます。  
#### ターミナル
```sh
dotnet new console -o <PROJECT_NAME>
```
### C. `<PROJECT_NAME>/<PROJECT_NAME>.csproj` の設定
デフォルトでは、カレントディレクトリでないディレクトリ内の *.cs までも監視対象としていますが `<EnableDefaultCompileItems>false</EnableDefaultCompileItems>` で解除できます。  
そして、`<Compile Include="./path/to/your/file/*.cs" />` で解除を解除できます。  

#### <PROJECT_NAME>/<PROJECT_NAME>.csproj
```xml
<Project Sdk="Microsoft.NET.Sdk">

  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>netcoreapp3.1</TargetFramework>
    <EnableDefaultCompileItems>false</EnableDefaultCompileItems>
  </PropertyGroup>

  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|AnyCPU'">
    <CheckForOverflowUnderflow>true</CheckForOverflowUnderflow>
  </PropertyGroup>

  <ItemGroup>
    <Compile Include="./lib/CSharp/**/*.cs" />
    <Compile Include="./src/**/*.cs" />
  </ItemGroup>

</Project>
```


## 3. ソースコードにライブラリを bundle する
自動でライブラリファイルからバンドルしてくれるコードを書きました: [lib/CSharp/expander.py](https://github.com/nullputra/nlptr-lib/blob/master/lib/CSharp/expander.py)  
使い方を以下の通りです。  

#### 用意するもの (1): src/Program.cs
```cs
// https://atcoder.jp/contests/abc087/tasks/arc090_b
using System;
using System.Linq;
using Lib.WeightedUnionFind;
class Program
{
    static void Main()
    {
        var nm = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
        int n = nm[0], m = nm[1];
        var uf = new WeightedUnionFind<int>(n, (x, y) => x + y, (x, y) => x - y, 0);
        for (int i = 0; i < m; i++)
        {
            var lrd = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
            int l = lrd[0], r = lrd[1], d = lrd[2];
            // Console.Error.WriteLine(l.ToString() + " " + r.ToString() + " " + d.ToString());
            if (!uf.TryUnite(l - 1, r - 1, d))
            {
                Console.WriteLine("No");
                return;
            }
        }
        Console.WriteLine("Yes");
    }
}
```

#### 用意するもの (2): lib/CSharp/DataStructures/WeightedUnionFind.cs
```cs
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
        public bool TryUnite(int x, int y, T w)
        {
            return Unite(x, y, w) || add(Weight(x), w).Equals(Weight(y));
        }
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
```

以上を用意して、ターミナルで下のコマンドを実行します。  
#### ターミナル
```sh
lib/CSharp/expander.py src/Program.cs > src/ProgramBundled.cs
```

#### 生成されるもの: src/ProgramBundled.cs
```cs
using Lib.WeightedUnionFind;
using System.Diagnostics;
using System.Linq;
using System;

class Program
{
    static void Main()
    {
        var nm = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
        int n = nm[0], m = nm[1];
        var uf = new WeightedUnionFind<int>(n, (x, y) => x + y, (x, y) => x - y, 0);
        for (int i = 0; i < m; i++)
        {
            var lrd = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
            int l = lrd[0], r = lrd[1], d = lrd[2];
            if (!uf.TryUnite(l - 1, r - 1, d))
            {
                Console.WriteLine("No");
                return;
            }
        }
        Console.WriteLine("Yes");
    }
}

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
        public bool TryUnite(int x, int y, T w)
        {
            return Unite(x, y, w) || add(Weight(x), w).Equals(Weight(y));
        }
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
```


## 4. 参考文献
- [C#で競技プログラミング(AtCoder)用のライブラリを作ろう！](https://qiita.com/kazurego7/items/38aa0afed75b483f199d)

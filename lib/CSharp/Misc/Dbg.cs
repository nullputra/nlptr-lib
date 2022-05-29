// python の print() のように, List<string> や int[n] などの中身をプリントする関数を作りました.
// デバッグ用です. ご自由にお使いください.
using System.Collections.Generic;
using System.Collections;
using System;
using Lib;

static partial class Dbg
{
    // 2 次元以下の配列に対応
    public static void Dump(string varName, params object[] prms)
    {
        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.Error.Write($"(dbg) {varName}: ");
        Console.ResetColor();
        for (int i = 0; i < prms.Length; i++)
        {
            if (i > 0) Console.Error.Write(", ");
            // prms[i] が string, char のとき
            if (prms[i].GetType() == typeof(string) || prms[i].GetType() == typeof(char))
            {
                // 文字列は黄色で表示
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.Error.Write(prms[i]);
                Console.ResetColor();
                continue;
            }
            if (typeof(StaticModInt<Mod998244353>).IsAssignableFrom(prms[i].GetType())
                || typeof(StaticModInt<Mod1000000007>).IsAssignableFrom(prms[i].GetType()))
            {
                // 赤紫色で表示
                Console.ForegroundColor = ConsoleColor.Magenta;
                Console.Error.Write(prms[i]);
                Console.ResetColor();
                continue;
            }
            // prms[i] が IEnumerable のとき
            if (typeof(IEnumerable).IsAssignableFrom(prms[i].GetType()))
            {
                string brackets = prms[i].GetType().IsArray ? "[]" : "{}";
                Console.Error.Write(brackets[0]);
                if (typeof(IEnumerable<int>).IsAssignableFrom(prms[i].GetType()))
                {
                    Console.Error.Write(String.Join(", ", (IEnumerable<int>)prms[i]));
                }
                else if (typeof(IEnumerable<long>).IsAssignableFrom(prms[i].GetType()))
                {
                    Console.Error.Write(String.Join(", ", (IEnumerable<long>)prms[i]));
                }
                else if (typeof(IEnumerable<double>).IsAssignableFrom(prms[i].GetType()))
                {
                    Console.Error.Write(String.Join(", ", (IEnumerable<double>)prms[i]));
                }
                else if (typeof(IEnumerable<char>).IsAssignableFrom(prms[i].GetType()))
                {
                    Console.Error.Write(String.Join(", ", (IEnumerable<char>)prms[i]));
                }
                else if (typeof(IEnumerable<string>).IsAssignableFrom(prms[i].GetType()))
                {
                    Console.Error.Write(String.Join(", ", (IEnumerable<string>)prms[i]));
                }
                else if (typeof(IEnumerable<StaticModInt<Mod998244353>>).IsAssignableFrom(prms[i].GetType()))
                {
                    // 赤紫色で表示
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    Console.Error.Write(String.Join(", ", (IEnumerable<StaticModInt<Mod998244353>>)prms[i]));
                    Console.ResetColor();
                }
                else if (typeof(IEnumerable<StaticModInt<Mod1000000007>>).IsAssignableFrom(prms[i].GetType()))
                {
                    // 赤紫色で表示
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    Console.Error.Write(String.Join(", ", (IEnumerable<StaticModInt<Mod1000000007>>)prms[i]));
                    Console.ResetColor();
                }
                // otherwise
                else
                {
                    Console.Error.Write("ERR");
                }
                Console.Error.Write(brackets[1]);
            }
            // prms[i] が IEnumerable 以外のとき
            else
            {
                Console.Error.Write(prms[i]);
            }
        }
        Console.Error.WriteLine();
    }

    // // 3 次元以上の配列を表示しようとした残骸 (未完成)
    // static string Parse(params object[] prms)
    // {
    //     bool eq(object p) => p.GetType() == typeof(char) || p.GetType() == typeof(string)
    //         || p.GetType() == typeof(StaticModInt<Mod998244353>) || p.GetType() == typeof(StaticModInt<Mod1000000007>);
    //     string res = "";
    //     if (typeof(IEnumerable).IsAssignableFrom(prms.GetType()))
    //     {
    //         for (int i = 0; i < prms.Length; i++)
    //         {
    //             if (i > 0) res += ", ";
    //             // prms[i] が IEnumerable のとき
    //             if (typeof(IEnumerable).IsAssignableFrom(prms[i].GetType()))
    //             {
    //                 string brackets = prms[i].GetType().IsArray ? "[]" : "{}";
    //                 res += brackets[0];
    //                 if (typeof(IEnumerable<int>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += String.Join(", ", (IEnumerable<int>)prms[i]);
    //                 }
    //                 else if (typeof(IEnumerable<long>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += String.Join(", ", (IEnumerable<long>)prms[i]);
    //                 }
    //                 else if (typeof(IEnumerable<double>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += String.Join(", ", (IEnumerable<double>)prms[i]);
    //                 }
    //                 else if (typeof(IEnumerable<char>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += "\0" + String.Join(", ", (IEnumerable<char>)prms[i]) + "\0";
    //                 }
    //                 else if (typeof(IEnumerable<string>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += "\0" + String.Join(", ", (IEnumerable<string>)prms[i]) + "\0";
    //                 }
    //                 else if (typeof(IEnumerable<StaticModInt<Mod998244353>>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += "\0" + String.Join(", ", (IEnumerable<StaticModInt<Mod998244353>>)prms[i]) + "\0";
    //                 }
    //                 else if (typeof(IEnumerable<StaticModInt<Mod1000000007>>).IsAssignableFrom(prms[i].GetType()))
    //                 {
    //                     res += "\0" + String.Join(", ", (IEnumerable<StaticModInt<Mod1000000007>>)prms[i]) + "\0";
    //                 }
    //                 else
    //                 {
    //                     res += "ERR";
    //                 }
    //                 res += brackets[1];
    //             }
    //             // prms[i] が IEnumerable 以外のとき
    //             else
    //             {
    //                 if (eq(prms[i])) res += "\0";
    //                 res += prms[i].ToString();
    //                 if (eq(prms[i])) res += "\0";
    //             }
    //         }
    //     }
    //     else
    //     {
    //         if (eq(prms)) res += "\0";
    //         res = prms.ToString();
    //         if (eq(prms)) res += "\0";
    //     }
    //     return res;
    // }
    // public static void Dump2(string varName, params object[] prms)
    // {
    //     Console.ForegroundColor = ConsoleColor.Cyan;
    //     Console.Error.Write($"(dbg) {varName}: ");
    //     Console.ResetColor();
    //     var res = Parse(prms).Split('\0');
    //     for (int i = 0; i < res.Length; i++)
    //     {
    //         if (i % 2 == 1) Console.ForegroundColor = ConsoleColor.Magenta;
    //         Console.Error.Write(res[i]);
    //         if (i % 2 == 1) Console.ResetColor();
    //     }
    //     Console.Error.WriteLine();
    // }
}

// Ref: https://atcoder.jp/contests/typical90/submissions/23944806, KumaTachiRen
using System;
using System.IO;
using System.Text;

namespace Lib.IStream
{
    public class IStream
    {
        public IStream() => sm = Console.OpenStandardInput();
        readonly Stream sm;
        readonly byte[] buf = new byte[1024];
        int len, idx;
        bool isEof = false;
        byte Byte()
        {
            if (isEof) throw new EndOfStreamException();
            if (idx >= len)
            {
                idx = 0;
                if ((len = sm.Read(buf, 0, 1024)) <= 0)
                {
                    isEof = true;
                    return 0;
                }
            }
            return buf[idx++];
        }
        public char Char()
        {
            byte b = 0;
            while (b < 33 || 126 < b) b = Byte();
            return (char)b;
        }
        public string Str()
        {
            var sb = new StringBuilder();
            for (char c = Char(); c >= 33 && c <= 126; c = (char)Byte()) sb.Append(c);
            return sb.ToString();
        }
        public long Long()
        {
            long x = 0;
            byte b = 0;
            bool isPosi = true;
            while (b != '-' && (b < '0' || '9' < b)) b = Byte();
            if (b == '-')
            {
                isPosi = false;
                b = Byte();
            }
            for (; true; b = Byte())
            {
                if (b < '0' || '9' < b) return isPosi ? x : -x;
                x = x * 10 + b - '0';
            }
        }
        public int Int() => (int)Long();
        public double Double() => double.Parse(Str());
        public T[] Arr<T>(int n, Func<T> f)
        {
            var a = new T[n];
            for (int i = 0; i < n; i++) a[i] = f();
            return a;
        }
    }
}

// Ref: https://github.com/key-moon/CSComproLib/blob/master/Library/BitOperation/PopCount.cs
using System.Runtime.CompilerServices;

namespace Lib.PopCount
{
    class BitOperation
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static byte PopCount(ulong n)
        {
            unchecked
            {
                n = (n & 0x5555555555555555ul) + ((n >> 1) & 0x5555555555555555ul);
                n = (n & 0x3333333333333333ul) + ((n >> 2) & 0x3333333333333333ul);
                n = (n & 0x0f0f0f0f0f0f0f0ful) + ((n >> 4) & 0x0f0f0f0f0f0f0f0ful);
                n = (n & 0x00ff00ff00ff00fful) + ((n >> 8) & 0x00ff00ff00ff00fful);
                n = (n & 0x0000ffff0000fffful) + ((n >> 16) & 0x0000ffff0000fffful);
                return (byte)((n & 0x00000000fffffffful) + ((n >> 32) & 0x00000000fffffffful));
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static byte PopCount(long n) => n < 0 ? (byte)(PopCount((ulong)(-n)) + 1) : PopCount((ulong)n);
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static byte PopCount(uint n)
        {
            unchecked
            {
                n = (n & 0x55555555u) + ((n >> 1) & 0x55555555u);
                n = (n & 0x33333333u) + ((n >> 2) & 0x33333333u);
                n = (n & 0x0f0f0f0fu) + ((n >> 4) & 0x0f0f0f0fu);
                n = (n & 0x00ff00ffu) + ((n >> 8) & 0x00ff00ffu);
                return (byte)((n & 0x0000ffffu) + ((n >> 16) & 0x0000ffffu));
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static byte PopCount(int n) => n < 0 ? (byte)(PopCount((uint)(-n)) + 1) : PopCount((uint)n);
    }
}

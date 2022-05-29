using System.Diagnostics;
using Mint = Lib.StaticModInt<Lib.Mod1000000007>;

class ModIntTest
{
    static void Main()
    {
        var x = new Mint(0);
        x -= 1;
        Debug.Assert(x == 1000000006);
    }
}

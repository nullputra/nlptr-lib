using System.Collections.Generic;

namespace Lib.HashMap
{
    public class HashMap<K, V> : Dictionary<K, V>
    {
        public HashMap() : base() { }
        public HashMap(int cap) : base(cap) { }
        new public V this[K i]
        {
            get
            {
                V v;
                return TryGetValue(i, out v) ? v : base[i] = default(V);
            }
            set { base[i] = value; }
        }
    }
}

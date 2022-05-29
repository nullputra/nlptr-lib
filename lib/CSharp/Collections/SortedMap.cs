using System.Collections.Generic;

namespace Lib.SortedMap
{
    public class SortedMap<K, V> : SortedDictionary<K, V>
    {
        public SortedMap() : base() { }
        public SortedMap(IComparer<K> cmp) : base(cmp) { }
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

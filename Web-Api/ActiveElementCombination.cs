namespace PCGAPI.WebAPI
{
    public record ActiveElementCombination(List<string> Elements, List<string> Included)
    {
        public int ElementCount => Elements.Count;
        public int IncludedCount => Included.Count;
        public string this[int index] => Elements[index];
        public int[] IncludedIndices
        {
            get
            {
                int[] indices = new int[IncludedCount];

                for (int i = 0; i < indices.Length; ++i)
                {
                    indices[i] = Elements.IndexOf(Included[i]);
                }

                return indices;
            }
        }
    }
}

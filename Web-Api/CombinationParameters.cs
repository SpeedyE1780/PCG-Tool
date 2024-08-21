namespace PCGAPI.WebAPI
{
    public record CombinationParameters(List<string> Elements)
    {
        internal int Count => Elements.Count;
        internal string this[int index] => Elements[index];
    }

    public record MinimumElementCombination(List<string> Elements, int MinimumElements)
    {
        internal int ElementCount => Elements.Count;
        internal string this[int index] => Elements[index];
    }

    public record ActiveElementCombination(List<string> Elements, List<string> Included)
    {
        internal int ElementCount => Elements.Count;
        internal int IncludedCount => Included.Count;
        internal string this[int index] => Elements[index];
        internal int[] IncludedIndices
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

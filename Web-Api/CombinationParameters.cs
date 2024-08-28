namespace PCGAPI.WebAPI
{
    /// <summary>
    /// List of elements used to generate a combination
    /// </summary>
    /// <param name="Elements">Elements used to generate a combination</param>
    public record CombinationParameters(List<string> Elements)
    {
        internal int Count => Elements.Count;
        internal string this[int index] => Elements[index];
    }

    /// <summary>
    /// List of elements used to generate a combination with a minimum element count
    /// </summary>
    /// <param name="Elements">Elements used to generate a combination</param>
    /// <param name="MinimumElements">Minimum count of elements in generated combination</param>
    public record MinimumElementCombination(List<string> Elements, int MinimumElements)
    {
        internal int ElementCount => Elements.Count;
        internal string this[int index] => Elements[index];
    }

    /// <summary>
    /// List of elements used to generate a combination with Included elements
    /// </summary>
    /// <param name="Elements">Elements used to generate a combination</param>
    /// <param name="Included">Included elements in generated combination</param>
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

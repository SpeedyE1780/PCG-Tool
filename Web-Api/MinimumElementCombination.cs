namespace PCGAPI.WebAPI
{
	public record MinimumElementCombination(List<string> Elements, int MinimumElements)
	{
		internal int ElementCount => Elements.Count;
		internal string this[int index] => Elements[index];
	}
}

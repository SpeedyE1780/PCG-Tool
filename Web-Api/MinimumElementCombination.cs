namespace PCGAPI.WebAPI
{
	public record MinimumElementCombination(List<string> Elements, int MinimumElements)
	{
		public int ElementCount => Elements.Count;
		public string this[int index] => Elements[index];
	}
}

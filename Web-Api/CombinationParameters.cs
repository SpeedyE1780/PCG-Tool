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

    /// <summary>
    /// Class containing all requests related to combinations
    /// </summary>
    public static class CombinationRequests
    {
        /// <summary>
        /// Generates a combination from a list of elements
        /// </summary>
        /// <param name="parameters">List of strings used</param>
        /// <returns>The generated combination</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     { 
        ///         "elements": ["Red", "Blue", "Green", "Purple", "Pink", "Yellow"] 
        ///     }
        /// 
        /// Sample Response:
        ///
        ///     [ "Blue", "Purple", "Yellow" ]
        /// </remarks>
        public static List<string> GenerateCombination(CombinationParameters parameters)
        {
            List<string> result = [];

            PCGEngine.GenerateCombination(parameters.Count, (index, included) =>
            {
                if (included)
                {
                    result.Add(parameters[index]);
                }
            });

            return result;
        }

        /// <summary>
        /// Generates a combination with at least x elements in it
        /// </summary>
        /// <param name="combinationParameters">List of strings and minimum element count</param>
        /// <returns>The generated combination with at least x elements</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "elements": ["Red", "Blue", "Green", "Purple", "Pink", "Yellow"],
        ///         "minimumElements": 5
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [ "Red", "Blue", "Purple", "Pink", "Yellow" ]
        /// </remarks>
        public static List<string> GenerateCombinationWithMinimumElement(MinimumElementCombination combinationParameters)
        {
            List<string> result = [];

            PCGEngine.GenerateCombination(combinationParameters.ElementCount, combinationParameters.MinimumElements, (index, included) =>
            {
                if (included)
                {
                    result.Add(combinationParameters[index]);
                }
            });

            return result;
        }

        /// <summary>
        /// Generate a combination with elements included
        /// </summary>
        /// <param name="combinationParameters">List of strings and included elements</param>
        /// <returns>The generated combination with the included elements</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "elements": ["Red", "Blue", "Green", "Purple", "Pink", "Yellow"],
        ///         "included": ["Red", "Green", "Pink"]
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [ "Red", "Blue", "Green", "Purple", "Pink", "Yellow" ]
        /// </remarks>
        public static List<string> GenerateCombinationWithActiveElement(ActiveElementCombination combinationParameters)
        {
            List<string> result = [];

            PCGEngine.GenerateCombination(combinationParameters.ElementCount, combinationParameters.IncludedIndices, combinationParameters.IncludedCount, (index, included) =>
            {
                if (included)
                {
                    result.Add(combinationParameters[index]);
                }
            });

            return result;
        }
    }
}

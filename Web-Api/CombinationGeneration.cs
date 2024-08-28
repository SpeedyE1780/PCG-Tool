namespace PCGAPI.WebAPI
{
    /// <summary>
    /// Class containing all requests related to combinations
    /// </summary>
    public static class CombinationGeneration
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

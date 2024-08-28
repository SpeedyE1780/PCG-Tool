namespace PCGAPI.WebAPI
{
    /// <summary>
    /// Class containing all requests related to sequence generation
    /// </summary>
    public static class SequenceGeneration
    {
        /// <summary>
        /// Generate Dictionary from list of nodes
        /// </summary>
        /// <param name="sequenceNodes">List of nodes</param>
        /// <returns>Dictionary with the node id as key as node as value</returns>
        private static Dictionary<int, SequenceNodeImplementation> GenerateSequenceDictionary(List<SequenceNode> sequenceNodes)
        {
            Dictionary<int, SequenceNodeImplementation> nodes = [];

            foreach (var node in sequenceNodes)
            {
                if (!nodes.TryGetValue(node.ID, out SequenceNodeImplementation? current))
                {
                    current = new SequenceNodeImplementation(node.ID);
                    nodes[node.ID] = current;
                }

                foreach (var next in node.NextNodes)
                {
                    if (!nodes.TryGetValue(next, out SequenceNodeImplementation? nextNode))
                    {
                        nextNode = new SequenceNodeImplementation(next);
                        nodes[next] = nextNode;
                    }

                    current.Children.Add(nextNode);
                }
            }

            return nodes;
        }

        /// <summary>
        /// Generate a non cyclic sequence
        /// </summary>
        /// <param name="parameters">Parameters used to generate sequence</param>
        /// <returns>List of node ids forming sequence</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///       "start": {
        ///         "id": 0,
        ///         "nextNodes": [
        ///           1, 2, 3, 4
        ///         ]
        ///       },
        ///       "nodes": [
        ///         {
        ///           "id": 0,
        ///           "nextNodes": [
        ///             1, 2, 3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 1,
        ///           "nextNodes": [
        ///             2, 3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 2,
        ///           "nextNodes": [
        ///             3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 3,
        ///           "nextNodes": [
        ///             4
        ///           ]
        ///         },
        ///         {
        ///           "id": 4,
        ///           "nextNodes": []
        ///         }
        ///       ]
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [ 0, 1, 2 ]
        /// </remarks>
        public static List<int> GenerateSequence(SequenceParameters parameters)
        {
            Dictionary<int, SequenceNodeImplementation> nodes = GenerateSequenceDictionary(parameters.Nodes);
            List<int> sequence = [];

            ISequenceNode currentNode = nodes[parameters.Start.ID];
            PCGEngine.GenerateSequence(currentNode, index =>
            {
                sequence.Add(((SequenceNodeImplementation)currentNode).ID);

                if (index == -1)
                {
                    return 0;
                }

                currentNode = currentNode.NextNodes.ElementAt(index);
                return currentNode.NextCount;
            });

            return sequence;
        }

        /// <summary>
        /// Generate a cyclic sequence
        /// </summary>
        /// <param name="parameters">Parameters used to generate sequence</param>
        /// <returns>List of node ids forming sequence</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///       "start": {
        ///         "id": 0,
        ///         "nextNodes": [
        ///           0, 1, 2, 3, 4
        ///         ]
        ///       },
        ///       "nodes": [
        ///         {
        ///           "id": 0,
        ///           "nextNodes": [
        ///             0, 1, 2, 3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 1,
        ///           "nextNodes": [
        ///             0, 1, 2, 3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 2,
        ///           "nextNodes": [
        ///             0, 1, 2, 3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 3,
        ///           "nextNodes": [
        ///             0, 1, 2, 3, 4
        ///           ]
        ///         },
        ///         {
        ///           "id": 4,
        ///           "nextNodes": [
        ///             0, 1, 2, 3, 4
        ///           ]
        ///         }
        ///       ],
        ///       "sequenceLength": 20
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [ 0, 1, 2, 4, 0, 4, 4, 3, 3, 2, 4, 0, 0, 1, 2, 1, 1, 0, 2, 2 ]
        /// </remarks>
        public static List<int> GenerateCyclicSequence(CyclicSequenceParameters parameters)
        {
            Dictionary<int, SequenceNodeImplementation> nodes = GenerateSequenceDictionary(parameters.Nodes);
            List<int> sequence = [];

            ISequenceNode currentNode = nodes[parameters.Start.ID];
            PCGEngine.GenerateCyclicSequence(currentNode, parameters.SequenceLength, index =>
            {
                sequence.Add(((SequenceNodeImplementation)currentNode).ID);

                if (index == -1)
                {
                    return 0;
                }

                currentNode = currentNode.NextNodes.ElementAt(index);
                return currentNode.NextCount;
            });

            return sequence;
        }
    }
}

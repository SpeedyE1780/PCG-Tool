namespace PCGAPI.WebAPI
{
    /// <summary>
    /// Class containing all requests related to level generation
    /// </summary>
    public static class LevelGeneration
    {
        /// <summary>
        /// Generates a level that follows a single axis
        /// </summary>
        /// <param name="parameters">Parameters used to generate level</param>
        /// <returns>List of node positions</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "nodeCount": 250,
        ///         "nodeSize": 1,
        ///         "startPosition": {
        ///           "x": 0,
        ///           "y": 0,
        ///           "z": 0
        ///         },
        ///         "offset": {
        ///           "x": 0,
        ///           "y": 0,
        ///           "z": 1
        ///         }
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 0
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 1
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 2
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 3
        ///         }
        ///     ]
        /// </remarks>
        public static List<Vector3> SimpleLevelGeneration(SimpleGenerationParameters parameters)
        {
            List<Vector3> positions = [];

            PCGEngine.SimpleGeneration(parameters.GenerationParameters, Vector3Helper.ToEngine(parameters.Offset), position =>
            {
                positions.Add(Vector3Helper.ToWebAPI(position));
            });

            return positions;
        }

        /// <summary>
        /// Generates a level that follows multiple axes
        /// </summary>
        /// <param name="parameters">Parameters used to generate level</param>
        /// <returns>List of node positions</returns>
        /// <remarks>
        /// Sample Request Body:
        ///     
        ///     {
        ///         "nodeCount": 250,
        ///         "nodeSize": 1,
        ///         "startPosition": {
        ///           "x": 0,
        ///           "y": 0,
        ///           "z": 0
        ///         },
        ///         "axes": 63, (This is the result of combining the axes together using Bit wise or: 1 | 2 | 4 | 8 | 16 | 32 = 63)
        ///         "disableOverlap": true
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 0
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": -1
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 1,
        ///             "z": -1
        ///         }
        ///     ]
        /// </remarks>
        public static List<Vector3> MultiDimensionLevelGeneration(MultiDimensionParameters parameters)
        {
            List<Vector3> positions = [];
            GenerationParameters generationParameters = parameters.GenerationParameters;
            PCGEngine.MultiDimensionalGeneration(generationParameters, parameters.Axes, parameters.DisableOverlap, position =>
            {
                positions.Add(Vector3Helper.ToWebAPI(position));
            });

            return positions;
        }

        /// <summary>
        /// Generates a level using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="parameters">Parameters used to generate level</param>
        /// <returns>List of node positions and adjacent nodes</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "nodeCount": 250,
        ///         "nodeSize": 1,
        ///         "startPosition": {
        ///           "x": 0,
        ///           "y": 0,
        ///           "z": 0
        ///         },
        ///         "expansionMode": 1,
        ///         "axes": 63 (This is the result of combining the axes together using Bit wise or: 1 | 2 | 4 | 8 | 16 | 32 = 63)
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [
        ///         {
        ///           "position": {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 0
        ///           },
        ///           "direction": 63
        ///         },
        ///         {
        ///           "position": {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 1
        ///           },
        ///           "direction": 8
        ///         },
        ///         {
        ///           "position": {
        ///               "x": 0,
        ///             "y": 0,
        ///             "z": -1
        ///           },
        ///           "direction": 4
        ///         },
        ///         {
        ///           "position": {
        ///               "x": -1,
        ///             "y": 0,
        ///             "z": 0
        ///           },
        ///           "direction": 2
        ///         },
        ///         {
        ///           "position": {
        ///               "x": 1,
        ///             "y": 0,
        ///             "z": 0
        ///           },
        ///           "direction": 1
        ///         },
        ///         {
        ///           "position": {
        ///               "x": 0,
        ///             "y": 1,
        ///             "z": 0
        ///           },
        ///           "direction": 32
        ///         },
        ///         {
        ///           "position": {
        ///               "x": 0,
        ///             "y": -1,
        ///             "z": 0
        ///           },
        ///           "direction": 16
        ///         }
        ///     ]
        /// </remarks>
        public static List<WFCNode> WaveFunctionCollapseGeneration(WaveFunctionCollapseParameters parameters)
        {
            List<WFCNode> nodes = [];
            GenerationParameters generationParameters = parameters.GenerationParameters;
            PCGEngine.WaveFunctionCollapseGeneration(generationParameters, parameters.ExpansionMode, parameters.Axes, (position, adjacentNodes) =>
            {
                nodes.Add(new(Vector3Helper.ToWebAPI(position), adjacentNodes));
            });

            return nodes;
        }

        /// <summary>
        /// Generate a 2D grid level using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="parameters">Parameters used to generate grid</param>
        /// <returns>List of nodes and adjacent nodes</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "width": 10,
        ///         "height": 10,
        ///         "plane": 51
        ///     }
        /// 
        /// Sample Response Body:
        /// 
        ///     [
        ///       {
        ///         "x": 0,
        ///         "y": 0,
        ///         "adjacentNodes": 6
        ///       },
        ///       {
        ///         "x": 1,
        ///         "y": 0,
        ///         "adjacentNodes": 5
        ///       },
        ///       {
        ///         "x": 0,
        ///         "y": 1,
        ///         "adjacentNodes": 10
        ///       },
        ///       {
        ///         "x": 1,
        ///         "y": 1,
        ///         "adjacentNodes": 9
        ///       }
        ///     ]
        /// </remarks>
        public static List<GridWFCNode2D> Grid2DWaveFunctionCollapseGeneration(GridWaveFunctionCollapseParameters2D parameters)
        {
            List<GridWFCNode2D> nodes = [];
            PCGEngine.WaveFunctionCollapseGeneration(parameters.Width, parameters.Height, parameters.Plane, true, (x, y, adjacentNodes) =>
            {
                nodes.Add(new(x, y, adjacentNodes));
            });

            return nodes;
        }

        /// <summary>
        /// Generate a 3D grid level using the Wave Function Collapse Algorithm
        /// </summary>
        /// <param name="parameters">Parameters used to generate grid</param>
        /// <returns>List of nodes and adjacent nodes</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "width": 10,
        ///         "height": 10,
        ///         "depth": 10
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 0,
        ///             "adjacentNodes": 20
        ///         },
        ///         {
        ///             "x": 1,
        ///             "y": 0,
        ///             "z": 0,
        ///             "adjacentNodes": 4
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 1,
        ///             "z": 0,
        ///             "adjacentNodes": 38
        ///         },
        ///         {
        ///             "x": 1,
        ///             "y": 1,
        ///             "z": 0,
        ///             "adjacentNodes": 5
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "z": 1,
        ///             "adjacentNodes": 26
        ///         },
        ///         {
        ///             "x": 1,
        ///             "y": 0,
        ///             "z": 1,
        ///             "adjacentNodes": 25
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 1,
        ///             "z": 1,
        ///             "adjacentNodes": 42
        ///         },
        ///         {
        ///             "x": 1,
        ///             "y": 1,
        ///             "z": 1,
        ///             "adjacentNodes": 41
        ///         }
        ///     ]
        /// </remarks>
        public static List<GridWFCNode3D> Grid3DWaveFunctionCollapseGeneration(GridWaveFunctionCollapseParameters3D parameters)
        {
            List<GridWFCNode3D> nodes = [];
            PCGEngine.WaveFunctionCollapseGeneration(parameters.Width, parameters.Height, parameters.Depth, true, (x, y, z, adjacentNodes) =>
            {
                nodes.Add(new(x, y, z, adjacentNodes));
            });

            return nodes;
        }

        /// <summary>
        /// Generate a maze
        /// </summary>
        /// <param name="mazeParameters">Parameters used to generate maze</param>
        /// <returns>List of nodes in maze and adjacent nodes</returns>
        /// <remarks>
        /// Sample Request Body:
        /// 
        ///     {
        ///         "width": 10,
        ///         "height": 10,
        ///         "algorithm": 0
        ///     }
        ///     
        /// Sample Response:
        /// 
        ///     [
        ///         {
        ///             "x": 0,
        ///             "y": 0,
        ///             "adjacentNodes": 2
        ///         },
        ///         {
        ///             "x": 1,
        ///             "y": 0,
        ///             "adjacentNodes": 5
        ///         },
        ///         {
        ///             "x": 0,
        ///             "y": 1,
        ///             "adjacentNodes": 2
        ///         },
        ///         {
        ///             "x": 1,
        ///             "y": 1,
        ///             "adjacentNodes": 9
        ///         }
        ///     ]
        /// </remarks>
        public static List<MazeNode> MazeGeneration(MazeParameters mazeParameters)
        {
            List<MazeNode> nodes = [];
            PCGEngine.GenerateMaze(mazeParameters.Width, mazeParameters.Height, true, mazeParameters.Algorithm, (x, y, adjacentNodes) =>
            {
                nodes.Add(new MazeNode(x, y, adjacentNodes));
            });

            return nodes;
        }
    }
}

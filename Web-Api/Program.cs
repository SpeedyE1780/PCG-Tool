using Microsoft.OpenApi.Any;
using PCGAPI;
using PCGAPI.WebAPI;
using Swashbuckle.AspNetCore.SwaggerGen;

var builder = WebApplication.CreateBuilder(args);

static List<IOpenApiAny> GetEnumDescription<T>() where T : struct, Enum
{
    List<IOpenApiAny> description = [];

    foreach (var item in Enum.GetValuesAsUnderlyingType(typeof(T)))
    {
        string? name = Enum.GetName(typeof(T), item);
        description.Add(new OpenApiString($"{item} ({name})"));
    }

    return description;
}

static void AddEnumMapType<T>(SwaggerGenOptions setupAction) where T : struct, Enum
{
    setupAction.MapType<T>(() => new Microsoft.OpenApi.Models.OpenApiSchema()
    {
        Type = "integer",
        Format = "int32",
        Enum = GetEnumDescription<T>()
    });
}

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(setupAction =>
{
    AddEnumMapType<MazeAlgorithm>(setupAction);
    AddEnumMapType<MazeDirection>(setupAction);
    AddEnumMapType<LevelGenerationDirection>(setupAction);
    AddEnumMapType<Axis>(setupAction);
    AddEnumMapType<ExpansionMode>(setupAction);
});

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapPost("/combination/generate", (List<string> elements) =>
{
    List<string> result = [];

    PCGEngine.GenerateCombination(elements.Count, (index, included) =>
    {
        if (included)
        {
            result.Add(elements[index]);
        }
    });

    return result;
})
.WithName("GenerateCombination")
.WithOpenApi();

app.MapPost("/combination/generatewithminimumelement", (MinimumElementCombination combinationParameters) =>
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
})
.WithName("GenerateCombinationWithMinimumElement")
.WithOpenApi();

app.MapPost("/combination/generatewithactiveelement", (ActiveElementCombination combinationParameters) =>
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
})
.WithName("GenerateCombinationWithActiveElement")
.WithOpenApi();

app.MapPost("/maze/generate", (MazeParameters mazeParameters) =>
{
    List<MazeNode> nodes = [];
    PCGEngine.GenerateMaze(mazeParameters.Width, mazeParameters.Height, true, mazeParameters.Algorithm, (x, y, adjacentNodes) =>
            {
                nodes.Add(new MazeNode(x, y, adjacentNodes));
            });

    return nodes;
})
.WithName("Maze")
.WithOpenApi();

app.MapPost("/levelgeneration/multidimensiongeneration", (MultiDimensionParameters parameters) =>
{
    List<PCGAPI.WebAPI.Vector3> positions = [];
    GenerationParameters generationParameters = parameters.GetGenerationParameters();
    PCGEngine.MultiDimensionalGeneration(ref generationParameters, parameters.Axes, parameters.DisableOverlap, position =>
    {
        positions.Add(Vector3Helper.ToWebAPI(position));
    });

    return positions;
})
.WithName("LevelGenerationMultiDimensionGeneration")
.WithOpenApi();

app.MapPost("/levelgeneration/simplegeneration", (SimpleGenerationParameters parameters) =>
{
    List<PCGAPI.WebAPI.Vector3> positions = [];
    GenerationParameters generationParameters = parameters.GetGenerationParameters();
    PCGEngine.SimpleGeneration(ref generationParameters, parameters.Axes, position =>
    {
        positions.Add(Vector3Helper.ToWebAPI(position));
    });

    return positions;
})
.WithName("LevelGenerationSimpleGeneration")
.WithOpenApi();

app.MapPost("/levelgeneration/wavefunctioncollapsegeneration/generate", (WaveFunctionCollapseParameters parameters) =>
{
    List<WFCNode> nodes = [];
    GenerationParameters generationParameters = parameters.GetGenerationParameters();
    PCGEngine.WaveFunctionCollapseGeneration(ref generationParameters, parameters.ExpansionMode, parameters.Axes, (position, adjacentNodes) =>
    {
        nodes.Add(new(Vector3Helper.ToWebAPI(position), adjacentNodes));
    });

    return nodes;
})
.WithName("LevelGenerationWaveFunctionCollapseGeneration")
.WithOpenApi();

app.MapPost("/levelgeneration/wavefunctioncollapsegeneration/grid2d", (GridWaveFunctionCollapseParameters2D parameters) =>
{
    List<GridWFCNode2D> nodes = [];
    PCGEngine.WaveFunctionCollapseGeneration(parameters.Width, parameters.Height, parameters.Plane, true, (x, y, adjacentNodes) =>
    {
        nodes.Add(new(x, y, adjacentNodes));
    });

    return nodes;
})
.WithName("LevelGenerationWaveFunctionCollapseGenerationGrid2D")
.WithOpenApi();

app.MapPost("/levelgeneration/wavefunctioncollapsegeneration/grid3d", (GridWaveFunctionCollapseParameters3D parameters) =>
{
    List<GridWFCNode3D> nodes = [];
    PCGEngine.WaveFunctionCollapseGeneration(parameters.Width, parameters.Height, parameters.Depth, true, (x, y, z, adjacentNodes) =>
    {
        nodes.Add(new(x, y, z, adjacentNodes));
    });

    return nodes;
})
.WithName("LevelGenerationWaveFunctionCollapseGenerationGrid3D")
.WithOpenApi();

app.Run();

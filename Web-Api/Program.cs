using PCGAPI;
using PCGAPI.WebAPI;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

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
.WithName("LevelGenerationMultiDimension")
.WithOpenApi();

app.Run();

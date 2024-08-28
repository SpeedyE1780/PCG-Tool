using Microsoft.OpenApi.Any;
using PCGAPI;
using PCGAPI.WebAPI;
using Swashbuckle.AspNetCore.SwaggerGen;
using System.Reflection;

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
    setupAction.SwaggerDoc("v1", new Microsoft.OpenApi.Models.OpenApiInfo()
    {
        Version = "v1",
        Title = "PCG Engine API",
        Description = "A web API for generating procedural content"
    });

    var xmlFileName = $"{Assembly.GetExecutingAssembly().GetName().Name}.xml";
    setupAction.IncludeXmlComments(Path.Combine(AppContext.BaseDirectory, xmlFileName));

    AddEnumMapType<MazeAlgorithm>(setupAction);
    AddEnumMapType<MazeDirection>(setupAction);
    AddEnumMapType<LevelGenerationDirection>(setupAction);
    AddEnumMapType<Axis>(setupAction);
    AddEnumMapType<ExpansionMode>(setupAction);
    AddEnumMapType<Plane>(setupAction);
});
builder.Services.AddCors();

var app = builder.Build();
app.UseCors(builder => builder.AllowAnyMethod().AllowAnyHeader().AllowAnyOrigin());

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapPost("/combination/generate", CombinationGeneration.GenerateCombination)
.WithName("GenerateCombination")
.WithOpenApi();

app.MapPost("/combination/generatewithminimumelement", CombinationGeneration.GenerateCombinationWithMinimumElement)
.WithName("GenerateCombinationWithMinimumElement")
.WithOpenApi();

app.MapPost("/combination/generatewithactiveelement", CombinationGeneration.GenerateCombinationWithActiveElement)
.WithName("GenerateCombinationWithActiveElement")
.WithOpenApi();

app.MapPost("/levelgeneration/simplegeneration", LevelGeneration.SimpleLevelGeneration)
.WithName("LevelGenerationSimpleGeneration")
.WithOpenApi();

app.MapPost("/levelgeneration/multidimensiongeneration", LevelGeneration.MultiDimensionLevelGeneration)
.WithName("LevelGenerationMultiDimensionGeneration")
.WithOpenApi();

app.MapPost("/levelgeneration/wavefunctioncollapsegeneration/generate", LevelGeneration.WaveFunctionCollapseGeneration)
.WithName("LevelGenerationWaveFunctionCollapseGeneration")
.WithOpenApi();

app.MapPost("/levelgeneration/wavefunctioncollapsegeneration/grid2d", LevelGeneration.Grid2DWaveFunctionCollapseGeneration)
.WithName("LevelGenerationWaveFunctionCollapseGenerationGrid2D")
.WithOpenApi();

app.MapPost("/levelgeneration/wavefunctioncollapsegeneration/grid3d", LevelGeneration.Grid3DWaveFunctionCollapseGeneration)
.WithName("LevelGenerationWaveFunctionCollapseGenerationGrid3D")
.WithOpenApi();

app.MapPost("/maze/generate", LevelGeneration.MazeGeneration)
.WithName("MazeGeneration")
.WithOpenApi();

app.MapPost("/sequence/generate", SequenceGeneration.GenerateSequence)
.WithName("SequenceGenerate")
.WithOpenApi();

app.MapPost("/sequence/generatecyclicsequence", SequenceGeneration.GenerateCyclicSequence)
.WithName("SequenceGenerateCyclicSequence")
.WithOpenApi();

app.Run();

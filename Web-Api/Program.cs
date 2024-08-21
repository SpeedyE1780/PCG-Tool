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

    PCGAPI.PCGEngine.GenerateCombination(elements.Count, (index, included) =>
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

app.Run();

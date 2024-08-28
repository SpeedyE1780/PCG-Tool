# PCG-Tool

## Description

The PCG Tool is made up of the C++ DLL library that can be used with C++ and other languages by using the C DLL.

This library can be used with C#, Unity, Unreal and Python.

A REST API is available to use the library with languages not yet implemented.

The library can be previewed using the web app.

## Documentation

- [PCG Engine Manual](./Documentation/Index.html)
- [PCG Engine Documentation](./PCG%20Engine/docs/pcg-engine/html/index.html)
- [C# Wrapper Documentation](./C#-PCG-Wrapper/docs/html/index.html)
- [Python Wrapper Documentation](./Python/docs/html/index.html)

## [PCG Engine](./PCG%20Engine/)

The PCG Engine contains multiple libraries used to generate levels, mazes, sequences and combination.

The output are tested by using golden values to preserve the same behavior after making changes to the implementation.

## [C# Wrapper](./C#-PCG-Wrapper/)

The C# Wrapper exposes all native functions to C# and can be used with Unity.

The output is tested using the same golden values in the PCG Engine tests to make sure the output matches.

## [GAM703-Engine Demo](./GAM703-Engine/)

This is a demo project using the game engine I developed during the GAM 703 course.

It shows how to use the library with native C++ projects.

## [Python Wrapper](./Python/)

The Python Wrapper exposes all native functions to python and can be used with pygame.

The output is tested using the same golden values in the PCG Engine tests to make sure the output matches.

## [Unity Package](./Unity/Unity%20PCG%20Wrapper/)

The Unity package uses the C# Wrapper to call the C++ library.

It adds editor windows to the engine to generate content during edit mode.

## [Unity Maze Demo](./Unity/Maze-Demo/)

The Unity Maze Demo is a project to showcase the engine's maze generation during play mode and edit mode.

## [Unreal](./Unreal/)

The Unreal plugin contains:

- **MyPCG Plugin:** Imports the C++ library and exposes function to convert classes from the PCG library to Unreal's classes.

- **PCG_Window:** Add editor window to the engine to generate content during edit mode.

## [PCG Web API](./Web-Api/)

The PCG Web API is an ASP.NET Core project that uses the C# Wrapper to expose the library functions to the API.

It uses post method and request body to get the parameters and returns a JSON representing the generated content.

## [PCG Web APP](./Web-App/)

The PCG Web APP is a NextJS website that's used to preview the PCG Web API responses.

Sequence and Combination results are shown as a string.

Level Generation results are previewed on the website using PlayCanvas.

The JSON representing the level is also shown on the screen in a text area and can be copied to use in an engine.

## [Journal](./Journal/)

The journal folder contains entries indicating links/questions used to solve the problems I was facing.

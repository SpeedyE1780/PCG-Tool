// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG_WindowCommands.h"

#define LOCTEXT_NAMESPACE "FPCG_WindowModule"

void FPCG_WindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenSimpleGenerationWindow, "Simple Generation", "Open Window to Spawn Actor on One Axis", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenMultiDimensionGenerationWindow, "Multi Dimension Generation", "Open Window to Spawn Actor on Multiple Axis", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenWaveFunctionCollapseGenerationWindow, "Wave Function Collapse Generation", "Open Window to Spawn Actor on Multiple Axis Following a Set of Rules", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenMazeWindow, "Maze Generation", "Open Window to Spawn Mazes", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenCombinationWindow, "Combination Window", "Open Window to Generate Combinations", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

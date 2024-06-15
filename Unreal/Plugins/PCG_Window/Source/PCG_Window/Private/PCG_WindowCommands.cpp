// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG_WindowCommands.h"

#define LOCTEXT_NAMESPACE "FPCG_WindowModule"

void FPCG_WindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "PCG_Window", "Bring up PCG_Window window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

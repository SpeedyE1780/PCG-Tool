// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PCG_WindowStyle.h"

class FPCG_WindowCommands : public TCommands<FPCG_WindowCommands>
{
public:

	FPCG_WindowCommands()
		: TCommands<FPCG_WindowCommands>(TEXT("PCG_Window"), NSLOCTEXT("Contexts", "PCG_Window", "PCG_Window Plugin"), NAME_None, FPCG_WindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
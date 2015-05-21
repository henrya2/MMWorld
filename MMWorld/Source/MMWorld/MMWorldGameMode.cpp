// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MMWorld.h"
#include "MMWorldGameMode.h"
#include "MMWorldHUD.h"
#include "MMWorldCharacter.h"

AMMWorldGameMode::AMMWorldGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/PlayerCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AMMWorldHUD> HUDClassFinder(TEXT("/Game/Blueprints/HUD/MMWorldHUD_BP"));

	// use our custom HUD class
	HUDClass = HUDClassFinder.Class;
}

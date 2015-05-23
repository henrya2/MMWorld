// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "MMWorldPlayerController.h"
#include "MMWorldCharacter.h"

AMMWorldPlayerController::AMMWorldPlayerController()
	: APlayerController(FObjectInitializer::Get())
{

}

void AMMWorldPlayerController::BuildInputStack(TArray<UInputComponent*>& InputStack)
{
	Super::BuildInputStack(InputStack);

	auto PlayerCharacter = Cast<AMMWorldCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		if (PlayerCharacter->InGameUIMode())
		{
			InputStack.RemoveSingle(PlayerCharacter->InputComponent);
		}
	}
}

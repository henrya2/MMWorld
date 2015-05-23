// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MMWorldPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API AMMWorldPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMMWorldPlayerController();

	virtual void BuildInputStack(TArray<UInputComponent*>& InputStack) override;
};

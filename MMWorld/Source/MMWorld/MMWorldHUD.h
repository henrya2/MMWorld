// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "MMWorldHUD.generated.h"

UCLASS()
class AMMWorldHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMMWorldHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

protected:
	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Texture)
	class UTexture2D* CrosshairTex;

};


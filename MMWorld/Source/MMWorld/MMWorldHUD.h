// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 

#include "GameFramework/HUD.h"
#include "MMWorldHUD.generated.h"

UCLASS()
class MMWORLD_API AMMWorldHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMMWorldHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void PreInitializeComponents();

	virtual void ShowHUD();

	virtual void BeginDestroy() override;

protected:
	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Texture)
	class UTexture2D* CrosshairTex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UGameHUDUI> UMGHudClass;

	class UGameHUDUI* UMGHud;
};


// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MMWorld.h"
#include "MMWorldHUD.h"
#include "GameHUDUI.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

AMMWorldHUD::AMMWorldHUD(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	CrosshairTex = nullptr;
	UMGHudClass = nullptr;
	UMGHud = nullptr;
}

void AMMWorldHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	if (CrosshairTex)
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
			(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

		// draw the crosshair
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}

void AMMWorldHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (UMGHudClass)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
		UMGHud = CreateWidget<UGameHUDUI>(PlayerController, UMGHudClass);
		if (UMGHud)
		{
			UMGHud->SetVisibility(bShowHUD ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
			UMGHud->AddToViewport(0);
		}
	}
}

void AMMWorldHUD::ShowHUD()
{
	Super::ShowHUD();

	if (UMGHud)
	{
		UMGHud->SetVisibility(bShowHUD ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}
}

void AMMWorldHUD::BeginDestroy()
{
	Super::BeginDestroy();

	if (UMGHud)
	{
		UMGHud->RemoveFromParent();
	}
}

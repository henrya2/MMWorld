// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "GameHUDUI.h"

UGameHUDUI::UGameHUDUI()
	: Super(FObjectInitializer::Get())
{

}

void UGameHUDUI::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!IsDesignTime())
	{

	}
}

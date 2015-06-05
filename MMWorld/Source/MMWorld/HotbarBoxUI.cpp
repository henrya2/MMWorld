// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "HotbarBoxUI.h"

UHotbarBoxUI::UHotbarBoxUI()
	: Super(FObjectInitializer::Get())
{

}

void UHotbarBoxUI::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!IsDesignTime())
	{

	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "HotbarUI.h"

UHotbarUI::UHotbarUI()
	: Super(FObjectInitializer::Get())
{

}

void UHotbarUI::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!IsDesignTime())
	{

	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HotbarUI.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API UHotbarUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UHotbarUI();

	virtual void OnWidgetRebuilt() override;
};

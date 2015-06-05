// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HotbarBoxUI.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API UHotbarBoxUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UHotbarBoxUI();

	virtual void OnWidgetRebuilt() override;
};

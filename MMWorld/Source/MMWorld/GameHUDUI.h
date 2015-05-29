// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameHUDUI.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API UGameHUDUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UGameHUDUI();

	virtual void OnWidgetRebuilt() override;
};

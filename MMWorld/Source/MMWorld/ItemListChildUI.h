// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemListChildUI.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API UItemListChildUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UItemListChildUI();

	virtual void OnWidgetRebuilt() override;

	void SetItemName(const FString& NameString);

protected:
	class UTextBlock* ItemNameText;
};

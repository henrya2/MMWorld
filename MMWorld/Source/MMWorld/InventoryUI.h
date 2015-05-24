// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventoryUI();

	virtual void BeginDestroy() override;

	virtual void OnWidgetRebuilt() override;

	void ShowUI(bool NewVisilbe);
	bool IsUIVisible() const;

protected:
	class UScrollBox* ItemsListBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UItemListChildUI> ItemListChildUIClass;
};

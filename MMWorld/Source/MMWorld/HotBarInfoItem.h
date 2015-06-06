// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MMWorldCommons.h"
#include "HotbarInfoItem.generated.h"

USTRUCT()
struct MMWORLD_API FHotbarInfoItem
{
	GENERATED_USTRUCT_BODY()

	FHotbarInfoItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AInventoryItem> MainItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AInventoryItem> SecondaryItem;

	void ChangeMainItem(class AInventoryItem* NewMainItem);
	void ChangeSecondaryItem(class AInventoryItem* NewSecondaryItem);

	void ChangeItem(class AInventoryItem* NewMainItem, EHotbarItemType HotbarItemType);
};

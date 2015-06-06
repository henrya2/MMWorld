// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "InventoryItem.h"
#include "HotbarInfoItem.h"

FHotbarInfoItem::FHotbarInfoItem()
{
	MainItem = nullptr;
	SecondaryItem = nullptr;
}

void FHotbarInfoItem::ChangeMainItem(class AInventoryItem* NewMainItem)
{
	ChangeItem(NewMainItem, EHotbarItemType::Main);
}

void FHotbarInfoItem::ChangeSecondaryItem(class AInventoryItem* NewSecondaryItem)
{
	ChangeItem(NewSecondaryItem, EHotbarItemType::Secondary);
}

void FHotbarInfoItem::ChangeItem(class AInventoryItem* NewMainItem, EHotbarItemType HotbarItemType)
{

}

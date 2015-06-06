// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	EquipedMainItem = nullptr;
	EquipedSecondaryItem = nullptr;

	HotbarItems.SetNum(HOTBAR_ITEMS_NUM);
}


// Called when the game starts
void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

class AInventoryItem* UInventoryComponent::GetEquipedItem(EHotbarItemType HotbarItemType)
{
	if (HotbarItemType == EHotbarItemType::Main)
	{
		return EquipedMainItem.Get();
	}
	else if (HotbarItemType == EHotbarItemType::Secondary)
	{
		return EquipedSecondaryItem.Get();
	}

	return nullptr;
}

void UInventoryComponent::EquipItem(class AInventoryItem* InventoryItem, EHotbarItemType HotbarItemType)
{
	if (GetEquipedItem(HotbarItemType) != InventoryItem)
	{
		if (GetEquipedItem(HotbarItemType))
		{
			GetEquipedItem(HotbarItemType)->Unequip();
		}

		InventoryItem->Equip();

		SetEquipItem(InventoryItem, HotbarItemType);
	}
}

void UInventoryComponent::UnEquipItem(class AInventoryItem* InventoryItem)
{
	if (InventoryItem == EquipedMainItem.Get())
	{
		InventoryItem->Unequip();
		EquipedMainItem = nullptr;
	}
	else if (InventoryItem == EquipedSecondaryItem.Get())
	{
		InventoryItem->Unequip();
		EquipedSecondaryItem = nullptr;
	}
}

void UInventoryComponent::PutItemIntoInventory(class AInventoryItem* InventoryItem)
{
	InventoryItems.Add(InventoryItem);
}

void UInventoryComponent::RemoveAnItemInInventory(class AInventoryItem* InventoryItem)
{
	InventoryItems.Remove(InventoryItem);
}

void UInventoryComponent::SetEquipItem(class AInventoryItem* InventoryItem, EHotbarItemType HotbarItemType)
{
	if (HotbarItemType == EHotbarItemType::Main)
	{
		EquipedMainItem = InventoryItem;
	}
	else if (HotbarItemType == EHotbarItemType::Secondary)
	{
		EquipedSecondaryItem = InventoryItem;
	}
}


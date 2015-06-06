// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "MMWorldCommons.h"
#include "HotBarInfoItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHotbarItemChangedDelegate, int32, HotbarItemIndex, TWeakObjectPtr<class AInventoryItem>, NewInventoryItem, EHotbarItemType, HotbarItemType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMWORLD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public:
	const TArray<TWeakObjectPtr<class AInventoryItem>>& GetInventoryItems() { return InventoryItems; }

	TArray<FHotbarInfoItem>& GetHotbarItems() { return HotbarItems; }

	class AInventoryItem* GetEquipedItem(EHotbarItemType HotbarItemType);

	int32 GetActiveHotbarItemIndex() const { return ActiveHotbarItemIndex; }
	void ActivateHotbarIndex(int32 Index);

	void ChangeHotbarItem(int32 HotbarItemIndex, class AInventoryItem* InventoryItem, EHotbarItemType HotbarItemType);

	void EquipItem(class AInventoryItem* InventoryItem, EHotbarItemType HotbarItemType);

	void UnEquipItem(class AInventoryItem* InventoryItem);

	void PutItemIntoInventory(class AInventoryItem* InventoryItem);

	void RemoveAnItemInInventory(class AInventoryItem* InventoryItem);

protected:
	void SetEquipItem(class AInventoryItem* InventoryItem, EHotbarItemType HotbarItemType);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TWeakObjectPtr<class AInventoryItem>> InventoryItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AInventoryItem> EquipedMainItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AInventoryItem> EquipedSecondaryItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHotbarInfoItem> HotbarItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ActiveHotbarItemIndex;
};

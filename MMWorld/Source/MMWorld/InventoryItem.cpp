// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "InventoryItem.h"
#include "MMWorldCharacter.h"

AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeEquiped = false;
	bInInventory = false;
}

FTransform AInventoryItem::GetHandBindPointTransform() const
{
	return FTransform::Identity;
}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInventoryItem::EnterInventory(class AMMWorldCharacter* NewOwningPawn)
{
	ActiveTrigger->SetActive(false);
	ActiveTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetOwner(NewOwningPawn);

	GetRootComponent()->SetHiddenInGame(true, true);

	NewOwningPawn->BindToItemsDummyNode(this);
	GetRootComponent()->SetRelativeTransform(FTransform::Identity);

	TouchedCharacter = nullptr;

	bInInventory = true;
}

void AInventoryItem::LeaveInventory(class AMMWorldCharacter* NewOwningPawn)
{
	ActiveTrigger->SetActive(true);
	ActiveTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetOwner(nullptr);

	GetRootComponent()->SetHiddenInGame(false, true);

	NewOwningPawn->UnbindToItemsDummyNode(this);

	bInInventory = false;
}

void AInventoryItem::OnStartUse_Implementation()
{
	if (TouchedCharacter.IsValid())
	{
		TouchedCharacter->PickupItem(this);
	}
}

void AInventoryItem::Equip()
{
	if (!bCanBeEquiped)
		return;

	GetRootComponent()->DetachFromParent();
	AMMWorldCharacter* MyPawn = Cast<AMMWorldCharacter>(GetOwner());
	MyPawn->BindToEquipItemPoint(this);
	GetRootComponent()->SetHiddenInGame(false, true);
	OnEquip();
}

void AInventoryItem::Unequip()
{
	AMMWorldCharacter* MyPawn = Cast<AMMWorldCharacter>(GetOwner());
	MyPawn->BindToItemsDummyNode(this);
	GetRootComponent()->SetRelativeTransform(FTransform::Identity);
	GetRootComponent()->SetHiddenInGame(true, false);

	OnUnequip();
}

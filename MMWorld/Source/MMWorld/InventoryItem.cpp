// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "InventoryItem.h"
#include "MMWorldCharacter.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

void AInventoryItem::EnterInventory(APawn* NewOwningPawn)
{
	auto MeshComponets = GetComponentsByClass(UMeshComponent::StaticClass());

	for (int32 i = 0; i < MeshComponets.Num(); ++i)
	{
		UMeshComponent* MeshComp = Cast<UMeshComponent>(MeshComponets[i]);
		if (MeshComp)
		{
			MeshComp->SetHiddenInGame(true);
		}
	}

	ActiveTrigger->SetActive(false);
	SetOwner(NewOwningPawn);
}

void AInventoryItem::LeaveInventory()
{
	auto MeshComponets = GetComponentsByClass(UMeshComponent::StaticClass());

	for (int32 i = 0; i < MeshComponets.Num(); ++i)
	{
		UMeshComponent* MeshComp = Cast<UMeshComponent>(MeshComponets[i]);
		if (MeshComp)
		{
			MeshComp->SetHiddenInGame(false);
		}
	}

	ActiveTrigger->SetActive(true);
	SetOwner(nullptr);
}

void AInventoryItem::OnStartUse_Implementation()
{
	if (TouchedCharacter.IsValid())
	{
		TouchedCharacter->PickupItem(this);
	}
}

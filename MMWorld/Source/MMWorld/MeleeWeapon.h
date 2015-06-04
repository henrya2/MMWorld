// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InventoryItem.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MMWORLD_API AMeleeWeapon : public AInventoryItem
{
	GENERATED_BODY()
	
public:
	AMeleeWeapon();
	
	virtual FTransform GetHandBindPointTransform() const override;

	virtual void OnStartPrimaryAction() override;
	virtual void OnStopPrimaryAction() override;
	virtual void OnStartSecondaryAction() override;
	virtual void OnStopSecondaryAction() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action)
	UAnimMontage* AttackAnimation;
};

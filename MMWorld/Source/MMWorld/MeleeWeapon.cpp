// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "MeleeWeapon.h"
#include "MMWorldCharacter.h"

AMeleeWeapon::AMeleeWeapon()
{
	bCanBeEquiped = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->AttachParent = GetRootComponent();

	AttackAnimation = nullptr;
}

FTransform AMeleeWeapon::GetHandBindPointTransform() const
{
	return Mesh->GetSocketTransform(TEXT("HandBindPoint"), RTS_Component);
}

void AMeleeWeapon::OnStartPrimaryAction()
{
	AMMWorldCharacter* PlayerCharacter = Cast<AMMWorldCharacter>(GetOwner());
	if (PlayerCharacter && AttackAnimation)
	{
		PlayerCharacter->PlayAnimMontage(AttackAnimation);
	}
}

void AMeleeWeapon::OnStopPrimaryAction()
{

}

void AMeleeWeapon::OnStartSecondaryAction()
{

}

void AMeleeWeapon::OnStopSecondaryAction()
{

}

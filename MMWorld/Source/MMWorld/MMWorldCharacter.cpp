// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MMWorld.h"
#include "MMWorldCharacter.h"
#include "InteractivebleActor.h"
#include "InventoryItem.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AMMWorldCharacter

AMMWorldCharacter::AMMWorldCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetMesh()->RelativeLocation = FVector(0, 0, -90);
	GetMesh()->RelativeRotation = FRotator(0, -90, 0);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	//FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;

	ThirdPersonCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonCameraArm"));
	ThirdPersonCameraArm->TargetOffset = FVector(0.f, 0.f, 0.f);
	ThirdPersonCameraArm->SetRelativeLocation(FVector(-40.0f, 0.f, 160.f));
	ThirdPersonCameraArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	ThirdPersonCameraArm->AttachTo(GetMesh());
	ThirdPersonCameraArm->TargetArmLength = 200.f;
	ThirdPersonCameraArm->bEnableCameraLag = false;
	ThirdPersonCameraArm->bEnableCameraRotationLag = false;
	ThirdPersonCameraArm->bUsePawnControlRotation = true; // let the controller handle the view rotation
	ThirdPersonCameraArm->bInheritYaw = true;
	ThirdPersonCameraArm->bInheritPitch = true;
	ThirdPersonCameraArm->bInheritRoll = false;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->AttachTo(ThirdPersonCameraArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	ThirdPersonCamera->FieldOfView = 90.0f;
	ThirdPersonCamera->bAutoActivate = false;
	ThirdPersonCamera->bIsActive = false;

	PrimaryActorTick.bCanEverTick = true;

	bIsFirstPersonPerspective = true;
}

void AMMWorldCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FirstPersonCamera->AttachTo(GetMesh(), TEXT("CameraEyePoint"));
}

void AMMWorldCharacter::SetFirstPersonPerspective(bool bNewFirstPersonPerspective)
{
	if (bIsFirstPersonPerspective != bNewFirstPersonPerspective)
	{
		bIsFirstPersonPerspective = bNewFirstPersonPerspective;

		if (bIsFirstPersonPerspective)
		{
			FirstPersonCamera->Activate();
			ThirdPersonCamera->Deactivate();
		}
		else
		{
			FirstPersonCamera->Deactivate();
			ThirdPersonCamera->Activate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMMWorldCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("ToggleThirdPerson", IE_Pressed, this, &AMMWorldCharacter::ToggleThirdPerson);

	InputComponent->BindAction("Use", IE_Pressed, this, &AMMWorldCharacter::OnStartUse);
	InputComponent->BindAction("Use", IE_Released, this, &AMMWorldCharacter::OnStopUse);

	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AMMWorldCharacter::OnStartPrimaryAction);
	InputComponent->BindAction("PrimaryAction", IE_Released, this, &AMMWorldCharacter::OnStopPrimaryAction);
	InputComponent->BindAction("SecondaryAction", IE_Pressed, this, &AMMWorldCharacter::OnStartSecondaryAction);
	InputComponent->BindAction("SecondaryAction", IE_Released, this, &AMMWorldCharacter::OnStopSecondaryAction);
	
	InputComponent->BindAxis("MoveForward", this, &AMMWorldCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMMWorldCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMMWorldCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMMWorldCharacter::LookUpAtRate);
}

void AMMWorldCharacter::ToggleThirdPerson()
{
	SetFirstPersonPerspective(!GetIsFirstPersonPerspective());
}

void AMMWorldCharacter::OnStartUse()
{
	if (ActiveInteractivebleActor.IsValid())
	{
		ActiveInteractivebleActor->StartUse();
	}
}

void AMMWorldCharacter::OnStopUse()
{
	if (ActiveInteractivebleActor.IsValid())
	{
		ActiveInteractivebleActor->StopUse();
	}
}

void AMMWorldCharacter::OnStartPrimaryAction()
{

}

void AMMWorldCharacter::OnStopPrimaryAction()
{

}

void AMMWorldCharacter::OnStartSecondaryAction()
{

}

void AMMWorldCharacter::OnStopSecondaryAction()
{

}

void AMMWorldCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMMWorldCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMMWorldCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMMWorldCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMMWorldCharacter::SetActiveInteractivebleActor(class AInteractivebleActor* NewInteractivebleActor)
{
	ActiveInteractivebleActor = NewInteractivebleActor;
}

void AMMWorldCharacter::PickupItem(class AInventoryItem* InventoryItem)
{
	PutItemIntoInventory(InventoryItem);
	InventoryItem->EnterInventory(this);
}

void AMMWorldCharacter::PutItemIntoInventory(class AInventoryItem* InventoryItem)
{
	InventoryItems.Add(InventoryItem);
}

void AMMWorldCharacter::RemoveAnItemInInventory(class AInventoryItem* InventoryItem)
{

	InventoryItems.Remove(InventoryItem);
}

void AMMWorldCharacter::LeaveAnItemInInventory(class AInventoryItem* InventoryItem)
{
	InventoryItem->LeaveInventory();
	RemoveAnItemInInventory(InventoryItem);
}

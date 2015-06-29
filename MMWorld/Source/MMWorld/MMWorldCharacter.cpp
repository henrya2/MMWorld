// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MMWorld.h"
#include "HotBarInfoItem.h"
#include "MMWorldCharacter.h"
#include "InventoryComponent.h"
#include "InteractivebleActor.h"
#include "InventoryItem.h"
#include "InventoryUI.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Engine/InputDelegateBinding.h"

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

	ItemsDummyNode = CreateDefaultSubobject<USceneComponent>(TEXT("ItemsDummyNode"));
	ItemsDummyNode->AttachParent = RootComponent;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	PrimaryActorTick.bCanEverTick = true;

	bIsFirstPersonPerspective = true;

	InventoryUIClass = nullptr;
	InventoryUI = nullptr;

	bInGameUIMode = false;

	//HotbarItems.SetNum(HOTBAR_ITEMS_NUM);
}

void AMMWorldCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FirstPersonCamera->AttachTo(GetMesh(), TEXT("CameraEyePoint"));
}

void AMMWorldCharacter::SetupGameUIInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAction("Backpack", IE_Pressed, this, &AMMWorldCharacter::ToggleBackpack);
}

void AMMWorldCharacter::CreateAndInitGameUIInputComponent()
{
	if (GameUIInputComponent == NULL)
	{
		GameUIInputComponent = ConstructObject<UInputComponent>(UInputComponent::StaticClass(), this, TEXT("GameUIInputComponent"));
		if (GameUIInputComponent)
		{
			SetupGameUIInputComponent(GameUIInputComponent);
			GameUIInputComponent->RegisterComponent();
			UBlueprintGeneratedClass* BGClass = Cast<UBlueprintGeneratedClass>(GetClass());
			if (BGClass != NULL)
			{
				GameUIInputComponent->bBlockInput = bBlockInput;
				UInputDelegateBinding::BindInputDelegates(BGClass, GameUIInputComponent);
			}
		}
	}
}

void AMMWorldCharacter::DestroyPlayerInputComponent()
{
	Super::DestroyPlayerInputComponent();

	if (GameUIInputComponent)
	{
		GameUIInputComponent->DestroyComponent();
		GameUIInputComponent = nullptr;
	}
}

void AMMWorldCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (IsLocallyControlled())
	{
		CreateAndInitGameUIInputComponent();
	}
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

void AMMWorldCharacter::ToggleBackpack()
{
	if (InventoryUI)
	{
		InventoryUI->ShowUI(!InventoryUI->IsUIVisible());
		SetInUIMode(InventoryUI->IsUIVisible());
	}
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
	if (InventoryComponent->GetEquipedItem(EHotbarItemType::Main))
	{
		InventoryComponent->GetEquipedItem(EHotbarItemType::Main)->OnStartPrimaryAction();
	}
}

void AMMWorldCharacter::OnStopPrimaryAction()
{
	if (InventoryComponent->GetEquipedItem(EHotbarItemType::Main))
	{
		InventoryComponent->GetEquipedItem(EHotbarItemType::Main)->OnStopPrimaryAction();
	}
}

void AMMWorldCharacter::OnStartSecondaryAction()
{
	if (InventoryComponent->GetEquipedItem(EHotbarItemType::Secondary))
	{
		InventoryComponent->GetEquipedItem(EHotbarItemType::Secondary)->OnStartSecondaryAction();
	}
}

void AMMWorldCharacter::OnStopSecondaryAction()
{
	if (InventoryComponent->GetEquipedItem(EHotbarItemType::Secondary))
	{
		InventoryComponent->GetEquipedItem(EHotbarItemType::Secondary)->OnStopSecondaryAction();
	}
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
	ActiveInteractivebleActor = nullptr;
	InventoryItem->EnterInventory(this);
}

void AMMWorldCharacter::PutItemIntoInventory(class AInventoryItem* InventoryItem)
{
	InventoryComponent->PutItemIntoInventory(InventoryItem);
}

void AMMWorldCharacter::RemoveAnItemInInventory(class AInventoryItem* InventoryItem)
{

	InventoryComponent->RemoveAnItemInInventory(InventoryItem);
}

void AMMWorldCharacter::DropAnItemInInventory(class AInventoryItem* InventoryItem)
{
	InventoryItem->LeaveInventory(this);
	RemoveAnItemInInventory(InventoryItem);
}

const TArray<TWeakObjectPtr<class AInventoryItem>>& AMMWorldCharacter::GetInventoryItems()
{
	return InventoryComponent->GetInventoryItems();
}

void AMMWorldCharacter::BindToItemsDummyNode(class AInventoryItem* InventoryItem)
{
	InventoryItem->GetRootComponent()->AttachTo(GetItemsDummyNode());
}

void AMMWorldCharacter::UnbindToItemsDummyNode(class AInventoryItem* InventoryItem)
{
	InventoryItem->GetRootComponent()->DetachFromParent();
}

void AMMWorldCharacter::EquipItem(class AInventoryItem* InventoryItem)
{
	InventoryComponent->EquipItem(InventoryItem, EHotbarItemType::Main);
}

void AMMWorldCharacter::UnequipItem(class AInventoryItem* InventoryItem)
{
	InventoryComponent->UnEquipItem(InventoryItem);
}

void AMMWorldCharacter::BindToEquipItemPoint(class AInventoryItem* InventoryItem)
{
	InventoryItem->AttachRootComponentTo(GetMesh(), TEXT("ItemHoldPointRight"));
}

float AMMWorldCharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate /*= 1.f*/, FName StartSectionName /*= NAME_None*/)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}

	return 0.0f;
}

void AMMWorldCharacter::StopAnimMontage(class UAnimMontage* AnimMontage /*= nullptr*/)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOutTime);
	}
}

void AMMWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
	{
		if (InventoryUI)
		{
			InventoryUI->RemoveFromParent();
			InventoryUI = nullptr;
		}

		if (InventoryUIClass)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			InventoryUI = CreateWidget<UInventoryUI>(PlayerController, InventoryUIClass);
			if (InventoryUI)
			{
				InventoryUI->SetVisibility(ESlateVisibility::Hidden);
				InventoryUI->AddToViewport(1);
			}
		}
	}
}

void AMMWorldCharacter::BeginDestroy()
{
	if (InventoryUI)
	{
		InventoryUI->RemoveFromParent();
		InventoryUI = nullptr;
	}

	Super::BeginDestroy();
}

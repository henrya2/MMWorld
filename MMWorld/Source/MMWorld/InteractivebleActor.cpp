// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "InteractivebleActor.h"
#include "MMWorldCharacter.h"
#include "InteractionsInterface.h"


// Sets default values
AInteractivebleActor::AInteractivebleActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ActiveTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ActiveTrigger"));
	ActiveTrigger->AttachParent = RootComponent;

	bTrackedByCharcter = false;
	TouchedCharacter = nullptr;
	NotifyTargetsSwitchTurnedIndex = 0;

	bTurnedOnOrOff = false;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractivebleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractivebleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractivebleActor::OnStartUse_Implementation()
{
	if (!bTurnedOnOrOff)
	{
		bTurnedOnOrOff = true;
		NotifyTargetsSwitchTurned(true, NotifyTargetsSwitchTurnedIndex);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("OnStartUse_Implementation"));
}

void AInteractivebleActor::OnStopUse_Implementation()
{

}

void AInteractivebleActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ActiveTrigger)
	{
		// Ensure delegate is bound (just once)
		ActiveTrigger->OnComponentBeginOverlap.RemoveDynamic(this, &AInteractivebleActor::ActiveTriggerTouched);
		ActiveTrigger->OnComponentEndOverlap.RemoveDynamic(this, &AInteractivebleActor::ActiveTriggerUntouched);
		ActiveTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractivebleActor::ActiveTriggerTouched);
		ActiveTrigger->OnComponentEndOverlap.AddDynamic(this, &AInteractivebleActor::ActiveTriggerUntouched);
	}
}

void AInteractivebleActor::NotifyTargetsSwitchTurned(bool bOnOrOff, int32 CustomParam)
{
	for (auto iter = TargetActors.CreateIterator(); iter; ++iter)
	{
		auto TargetActor = (*iter).Get();
		if (TargetActor)
		{
			IInteractionsInterface::Execute_SwitchTurned(TargetActor, bOnOrOff, CustomParam);
		}
	}
}

void AInteractivebleActor::ActiveTriggerTouched(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMMWorldCharacter* PlayerCharacter = Cast<AMMWorldCharacter>(Other);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetActiveInteractivebleActor(this);
		bTrackedByCharcter = true;
		TouchedCharacter = PlayerCharacter;
	}
}

void AInteractivebleActor::ActiveTriggerUntouched(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMMWorldCharacter* PlayerCharacter = Cast<AMMWorldCharacter>(Other);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetActiveInteractivebleActor(nullptr);
		ClearStates();
		bTrackedByCharcter = false;
		TouchedCharacter = nullptr;
	}
}

void AInteractivebleActor::StartUse()
{
	if (bTrackedByCharcter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6, FColor::Green, TEXT("StartUse"));
		OnStartUse();
	}
}

void AInteractivebleActor::StopUse()
{
	if (bTrackedByCharcter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6, FColor::Green, TEXT("StopUse"));
		OnStopUse();
	}
}

void AInteractivebleActor::ClearStates()
{
	OnClearStates();
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractivebleActor.generated.h"

UCLASS()
class MMWORLD_API AInteractivebleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractivebleActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void StartUse();
	void StopUse();

	void ClearStates();

	UFUNCTION(BlueprintImplementableEvent)
	void OnClearStates();

	UFUNCTION(BlueprintNativeEvent, Category = Use)
	void OnStartUse();

	UFUNCTION(BlueprintNativeEvent, Category = Use)
	void OnStopUse();

	virtual void OnStartUse_Implementation();
	virtual void OnStopUse_Implementation();

	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION(BlueprintCallable, Category = Interactions)
	void NotifyTargetsSwitchTurned(bool bOnOrOff, int32 CustomParam);

protected:
	UFUNCTION()
	void ActiveTriggerTouched(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ActiveTriggerUntouched(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trigger)
	UBoxComponent* ActiveTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TWeakObjectPtr<class AActor>> TargetActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AMMWorldCharacter> TouchedCharacter;

	UPROPERTY(VisibleAnywhere)
	bool bTrackedByCharcter;

	UPROPERTY(EditDefaultsOnly)
	bool bTurnedOnOrOff;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "31", UIMin = "0", UIMax = "31"))
	int32 NotifyTargetsSwitchTurnedIndex;
};

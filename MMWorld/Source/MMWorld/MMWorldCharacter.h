// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "MMWorldCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AMMWorldCharacter : public ACharacter
{
	GENERATED_BODY()

	friend class AInteractivebleActor;
public:
	AMMWorldCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

public:
	void SetFirstPersonPerspective(bool bNewFirstPersonPerspective);
	bool GetIsFirstPersonPerspective() const { return bIsFirstPersonPerspective; }

	void PickupItem(class AInventoryItem* InventoryItem);
	void PutItemIntoInventory(class AInventoryItem* InventoryItem);
	void RemoveAnItemInInventory(class AInventoryItem* InventoryItem);
	void LeaveAnItemInInventory(class AInventoryItem* InventoryItem);

	const TArray<TWeakObjectPtr<class AInventoryItem>>& GetInventoryItems() { return InventoryItems; }

protected:
	void ToggleThirdPerson();

	void OnStartUse();
	void OnStopUse();

	void OnStartPrimaryAction();
	void OnStopPrimaryAction();
	void OnStartSecondaryAction();
	void OnStopSecondaryAction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	void SetActiveInteractivebleActor(class AInteractivebleActor* NewInteractivebleActor);
	class AInteractivebleActor* GetActiveInteractivebleActor() const { return ActiveInteractivebleActor.Get(); }
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void PostInitializeComponents() override;

public:
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCamera; }

protected:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	/** third person camera */
	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	class UCameraComponent* ThirdPersonCamera;

	/** an arm for the third person camera */
	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	class USpringArmComponent* ThirdPersonCameraArm;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive)
	TWeakObjectPtr<class AInteractivebleActor> ActiveInteractivebleActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<TWeakObjectPtr<class AInventoryItem>> InventoryItems;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = View)
	bool bIsFirstPersonPerspective;
};


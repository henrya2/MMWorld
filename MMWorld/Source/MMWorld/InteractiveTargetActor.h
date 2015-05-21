#pragma once

#include "GameFramework/Actor.h"
#include "InteractionsInterface.h"
#include "InteractiveTargetActor.generated.h"

UCLASS()
class MMWORLD_API AInteractiveTargetActor
	: public AActor
	, public IInteractionsInterface
{
	GENERATED_BODY()
public:
	AInteractiveTargetActor();

	virtual void SwitchTurned_Implementation(bool bNewOnOrOff, int32 CustomParam);

	UFUNCTION(BlueprintImplementableEvent, Category = Interactive)
	void SwitchAllTurnedOnOrOff(bool bOnOrOff);

	UFUNCTION(BlueprintCallable, Category = Interactive)
	bool IsSwitchTurned(int32 Index);

	UFUNCTION(BlueprintCallable, Category = Interactive)
	bool IsSwitchAllTurnedOn();

	UFUNCTION(BlueprintCallable, Category = Interactive)
	bool IsSwitchAllTurnedOff();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "32", UIMin = "1", UIMax = "32"))
	int32 NeedSwitchTurnedNum;

	uint32 SwitchTurnedStates;
};
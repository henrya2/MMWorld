// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractivebleActor.h"
#include "MiscItem.h"
#include "CollectPartsTriggerActor.generated.h"

USTRUCT()
struct MMWORLD_API FCollectPartInfo
{
	GENERATED_USTRUCT_BODY()

	FCollectPartInfo();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMiscItem> PartItemType;

	UPROPERTY(EditAnywhere)
	bool bCollected;
};

/**
 * 
 */
UCLASS()
class MMWORLD_API ACollectPartsTriggerActor : public AInteractivebleActor
{
	GENERATED_BODY()

public:
	ACollectPartsTriggerActor();

	virtual void OnStartUse_Implementation();


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCollectPartInfo> NeedCollectParts;
};

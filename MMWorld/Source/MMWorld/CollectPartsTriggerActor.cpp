// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "CollectPartsTriggerActor.h"
#include "MMWorldCharacter.h"

FCollectPartInfo::FCollectPartInfo()
{
	bCollected = false;
	PartItemType = nullptr;
}

ACollectPartsTriggerActor::ACollectPartsTriggerActor()
{

}

void ACollectPartsTriggerActor::OnStartUse_Implementation()
{
	if (TouchedCharacter.IsValid())
	{
		for (int32 i = 0; i < NeedCollectParts.Num(); ++i)
		{
			if (!NeedCollectParts[i].bCollected)
			{
				TArray<TWeakObjectPtr<class AInventoryItem>> Inventory = TouchedCharacter->GetInventoryItems();

				for (int32 j = 0; j < Inventory.Num(); ++j)
				{
					if (NeedCollectParts[i].PartItemType == Inventory[j]->GetClass())
					{
						NeedCollectParts[i].bCollected = true;
						TouchedCharacter->DropAnItemInInventory(Inventory[j].Get());
						Inventory[j]->Destroy();
					}
				}
			}
		}
	}

	bool bFullyCollected = true;
	for (int32 i = 0; i < NeedCollectParts.Num(); ++i)
	{
		if (!NeedCollectParts[i].bCollected)
		{
			bFullyCollected = false;
			break;
		}
	}

	if (bFullyCollected)
	{
		if (!bTurnedOnOrOff)
		{
			bTurnedOnOrOff = true;
			NotifyTargetsSwitchTurned(true, NotifyTargetsSwitchTurnedIndex);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Fully collected to open"));
		}
	}
}

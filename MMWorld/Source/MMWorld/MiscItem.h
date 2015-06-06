#pragma once

#include "InventoryItem.h"
#include "MMWorldCommons.h"
#include "MiscItem.generated.h"

UCLASS()
class MMWORLD_API AMiscItem : public AInventoryItem
{
	GENERATED_BODY()
public:
	AMiscItem();

	EMiscItemType GetMiscItemType() const { return MiscItemType; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	EMiscItemType MiscItemType;
};
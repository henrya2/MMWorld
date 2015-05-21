#pragma once

#include "InteractionsInterface.generated.h"

UINTERFACE()
class MMWORLD_API UInteractionsInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class MMWORLD_API IInteractionsInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void SwitchTurned(bool bNewOnOrOff, int32 CustomParam);
};
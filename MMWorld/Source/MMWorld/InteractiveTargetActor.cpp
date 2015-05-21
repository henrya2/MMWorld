#include "MMWorld.h"
#include "InteractiveTargetActor.h"

AInteractiveTargetActor::AInteractiveTargetActor()
{
	NeedSwitchTurnedNum = 1;
	SwitchTurnedStates = 0;
}

void AInteractiveTargetActor::SwitchTurned_Implementation(bool bNewOnOrOff, int32 CustomParam)
{
	if (bNewOnOrOff)
	{
		SwitchTurnedStates |= 1 << CustomParam;
	}
	else
	{
		SwitchTurnedStates &= ~(1 << CustomParam);
	}

	if (IsSwitchAllTurnedOn())
	{
		SwitchAllTurnedOnOrOff(true);
	}
	else if (IsSwitchAllTurnedOff())
	{
		SwitchAllTurnedOnOrOff(false);
	}
}

bool AInteractiveTargetActor::IsSwitchTurned(int32 Index)
{
	return (SwitchTurnedStates & (1 << Index)) != 0;
}

bool AInteractiveTargetActor::IsSwitchAllTurnedOn()
{
	return (SwitchTurnedStates & (1 << (NeedSwitchTurnedNum - 1))) && !(SwitchTurnedStates & (SwitchTurnedStates + 1));
}

bool AInteractiveTargetActor::IsSwitchAllTurnedOff()
{
	return SwitchTurnedStates == 0;
}

#pragma once

#include "ItemConstants.generated.h"

UENUM()
enum class EMiscItemType : uint8
{
	InstallationPart,
	Garbage
};

UENUM()
enum class EEquipItemType : uint8
{
	Weapon,
	Shield,
};
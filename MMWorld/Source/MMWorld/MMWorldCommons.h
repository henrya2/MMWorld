#pragma once

#include "MMWorldCommons.generated.h"

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

UENUM()
enum class EHotbarItemType : uint8
{
	Main,
	Secondary,
};

#define HOTBAR_ITEMS_NUM 4
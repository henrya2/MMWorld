// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "ItemListChildUI.h"
#include "InventoryItem.h"
#include "MMWorldCharacter.h"
#include "Components/PanelWidget.h"
#include "Components/ContentWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UItemListChildUI::UItemListChildUI()
	: Super(FObjectInitializer::Get())
{
	ItemNameText = nullptr;
	InventoryItem = nullptr;
}

void UItemListChildUI::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	ItemNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	BackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UItemListChildUI::OnClickedBackButton);
	}
}

void UItemListChildUI::SetItemName(const FString& NameString)
{
	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(NameString));
	}
}

void UItemListChildUI::SetInventoryItem(AInventoryItem* NewInventoryItem)
{
	InventoryItem = NewInventoryItem;
}

void UItemListChildUI::OnClickedBackButton()
{
	if (InventoryItem.IsValid())
	{
		AMMWorldCharacter* PlayerCharacter = GetPlayerContext().GetPawn<AMMWorldCharacter>();
		if (PlayerCharacter)
		{
			PlayerCharacter->EquipItem(InventoryItem.Get());
		}
	}
}

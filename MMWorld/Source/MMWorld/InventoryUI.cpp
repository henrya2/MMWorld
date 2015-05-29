// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "Components/PanelWidget.h"
#include "Components/ScrollBox.h"
#include "InventoryUI.h"
#include "ItemListChildUI.h"
#include "MMWorldCharacter.h"
#include "InventoryItem.h"

UInventoryUI::UInventoryUI()
	: Super(FObjectInitializer::Get())
{
	ItemsListBox = nullptr;
	ItemListChildUIClass = nullptr;
}

void UInventoryUI::BeginDestroy()
{
	Super::BeginDestroy();
}

void UInventoryUI::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!IsDesignTime())
	{
		ItemsListBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ItemsListBox")));
		if (ItemsListBox)
		{

		}
	}
}

void UInventoryUI::ShowUI(bool NewVisilbe)
{
	if (IsUIVisible() != NewVisilbe)
	{
		SetVisibility(NewVisilbe ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);

		// Refresh the ItemList
		if (NewVisilbe && (ItemsListBox && ItemListChildUIClass))
		{
			ItemsListBox->ClearChildren();

			AMMWorldCharacter* PlayerCharacter = Cast<AMMWorldCharacter>(GetPlayerContext().GetPawn());
			if (PlayerCharacter)
			{
				auto PlayerInventoryItems = PlayerCharacter->GetInventoryItems();
				for (int32 i = 0; i < PlayerInventoryItems.Num(); ++i)
				{
					UItemListChildUI* ItemListChild = CreateWidget<UItemListChildUI>(GetPlayerContext().GetPlayerController(), ItemListChildUIClass);
					if (ItemListChild)
					{
						ItemsListBox->AddChild(ItemListChild);
						ItemListChild->SetItemName(PlayerInventoryItems[i]->GetItemName());
					}
				}
			}
		}

		{
			APlayerController* PlayerController = GetPlayerContext().GetPlayerController();

			if (PlayerController)
			{
				if (NewVisilbe)
				{
					PlayerController->bShowMouseCursor = true;
				}
				else
				{
					PlayerController->bShowMouseCursor = false;
				}
			}
		}

	}
}

bool UInventoryUI::IsUIVisible() const
{
	return GetVisibility() != ESlateVisibility::Hidden;
}

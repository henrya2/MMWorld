// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "Components/PanelWidget.h"
#include "Components/ScrollBox.h"
#include "InventoryUI.h"

UInventoryUI::UInventoryUI()
	: Super(FObjectInitializer::Get())
{
	ItemsListBox = nullptr;
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

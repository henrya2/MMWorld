// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "ItemListChildUI.h"
#include "Components/TextBlock.h"

UItemListChildUI::UItemListChildUI()
	: Super(FObjectInitializer::Get())
{
	ItemNameText = nullptr;
}

void UItemListChildUI::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	ItemNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}

void UItemListChildUI::SetItemName(const FString& NameString)
{
	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(NameString));
	}
}

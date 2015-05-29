// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "ItemListChildUI.h"
#include "Components/PanelWidget.h"
#include "Components/ContentWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UItemListChildUI::UItemListChildUI()
	: Super(FObjectInitializer::Get())
{
	ItemNameText = nullptr;
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

void UItemListChildUI::OnClickedBackButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("OnClickedBackButton"));
}

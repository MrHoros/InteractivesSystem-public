// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalPlayerPopupsSubsystem.h"
#include "Hint.h"
#include "Document.h"
#include "UObject/ConstructorHelpers.h"

UDocument* ULocalPlayerPopupsSubsystem::GetPlayerDocumentPopup() const
{
	return PlayerDocumentPopup;
}

UHint* ULocalPlayerPopupsSubsystem::GetPlayerHintPopup() const
{
	return PlayerHintPopup;
}

void ULocalPlayerPopupsSubsystem::SetHintClass(TSubclassOf<UHint> NewHintClass)
{
	HintClass = NewHintClass;
}

void ULocalPlayerPopupsSubsystem::SetDocumentClass(TSubclassOf<UDocument> NewDocumentClass)
{
	DocumentClass = NewDocumentClass;
}

void ULocalPlayerPopupsSubsystem::CreatePopups()
{
	if (!HintClass || !DocumentClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Hint or Document class not set"));
		return;
	}

	if (PlayerHintPopup || PlayerDocumentPopup)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Popups already created"));
		return;
	}
	//perform UE_LOG to show LocalPLayer
	UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: LocalPlayer is %s"), *LocalPlayer->GetName());

	PlayerHintPopup = NewObject<UHint>(LocalPlayer, HintClass);
	PlayerDocumentPopup = NewObject<UDocument>(LocalPlayer, DocumentClass);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Document.h"

void UDocument::ShowDocument_Implementation(FDocumentInfo DocumentInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("Document: %s"), *DocumentInfo.DocumentTitle);
	UE_LOG(LogTemp, Warning, TEXT("Document: %s"), *DocumentInfo.DocumentText.ToString());

	bIsDocumentShown = true;

}

void UDocument::HideDocument_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Document: Hiding"));

	bIsDocumentShown = false;
}

UWorld* UDocument::GetWorld() const
{
	if (GetOuter()->IsA(ULocalPlayer::StaticClass()))
	{
		return GetOuter()->GetWorld();
	}
	else
	{
		return nullptr;
	}
}
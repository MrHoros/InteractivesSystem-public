// Fill out your copyright notice in the Description page of Project Settings.


#include "Hint.h"


void UHint::ShowHint_Implementation(FHintInfo HintInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("Hint: %s"), *HintInfo.HintText.ToString());

	bIsHintShown = true;
}

void UHint::HideHint_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Hint: Hiding"));

	bIsHintShown = false;
}

UWorld* UHint::GetWorld() const
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

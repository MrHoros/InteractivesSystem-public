// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "LocalPlayerPopupsSubsystem.generated.h"

class UDocument;
class UHint;

UCLASS(Blueprintable)
class ACTIONADVENTURE_API ULocalPlayerPopupsSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UDocument* GetPlayerDocumentPopup() const;
	UHint* GetPlayerHintPopup() const;

private:
	TSubclassOf<UHint> HintClass;
	TSubclassOf<UDocument> DocumentClass;

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetOuter());

	UHint* PlayerHintPopup;
	UDocument* PlayerDocumentPopup;

	UFUNCTION(BlueprintCallable, Category = "Popups", meta = (AllowPrivateAccess = "true"))
	void SetHintClass(TSubclassOf<UHint> NewHintClass);

	UFUNCTION(BlueprintCallable, Category = "Popups", meta = (AllowPrivateAccess = "true"))
	void SetDocumentClass(TSubclassOf<UDocument> NewDocumentClass);
	
	UFUNCTION(BlueprintCallable, Category = "Popups", meta = (AllowPrivateAccess = "true"))
	void CreatePopups();
};

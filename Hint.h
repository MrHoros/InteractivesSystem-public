// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Internationalization/Text.h"
#include "Hint.generated.h"

USTRUCT(BlueprintType)
struct FHintInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText HintText;
};

UCLASS(Blueprintable)
class ACTIONADVENTURE_API UHint : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowHint(FHintInfo HintInfo);
	void ShowHint_Implementation(FHintInfo HintInfo);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HideHint();
	void HideHint_Implementation();

	UFUNCTION(BlueprintCallable)
	bool IsHintShown() const { return bIsHintShown; };

private:

	bool bIsHintShown = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Document.generated.h"

USTRUCT(BlueprintType)
struct FDocumentInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText DocumentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DocumentTitle;
};
UCLASS(Blueprintable)
class ACTIONADVENTURE_API UDocument : public UObject
{
	GENERATED_BODY()
	
public:

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactives")
	void ShowDocument(FDocumentInfo DocumentInfo);
	void ShowDocument_Implementation(FDocumentInfo DocumentInfo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HideDocument();
	void HideDocument_Implementation();

	UFUNCTION(BlueprintCallable)
	bool IsDocumentShown() const { return bIsDocumentShown; };

private:

	bool bIsDocumentShown = false;
};

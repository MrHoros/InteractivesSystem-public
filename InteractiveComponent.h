// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractivesInterface.h"
#include "Document.h"
#include "Hint.h"
#include "InteractiveComponent.generated.h"

class Document;
class Hint;
class ULocalPlayerPopupsSubsystem;

UENUM(BlueprintType)
enum class EInteractiveType : uint8
{
	IT_Default UMETA("Default"),
	IT_Document UMETA(DisplayName = "Document"),
	IT_Hint UMETA(DisplayName = "Hint")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UInteractiveComponent : public USceneComponent, public IInteractivesInterface
{
	GENERATED_BODY()

public:	
	UInteractiveComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactives")
	void Interact();
	virtual void Interact_Implementation() override;

	void SetEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure)
	bool IsEnabled() const { return bIsEnabled; }

protected:
	virtual void BeginPlay() override;

	void HandleCurrentInteractiveType();

private:
	bool bIsEnabled = true;

	ULocalPlayerPopupsSubsystem* LocalPlayerPopupsSubsystem;

	UPROPERTY(EditAnywhere, Category = "Interactive", meta = (AllowPrivateAccess = "true"))
	EInteractiveType InteractiveType = EInteractiveType::IT_Default;

	UPROPERTY(EditAnywhere, Category = "Interactive", meta = (MultiLine = "true", AllowPrivateAccess = "true", EditCondition = "InteractiveType == EInteractiveType::IT_Document", EditConditionHides))
	FDocumentInfo DocumentInfo;

	UPROPERTY(EditAnywhere, Category = "Interactive", meta = (MultiLine = "true", AllowPrivateAccess = "true", EditCondition = "InteractiveType == EInteractiveType::IT_Hint", EditConditionHides))
	FHintInfo HintInfo;

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif
};

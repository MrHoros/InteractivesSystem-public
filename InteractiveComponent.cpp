// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InteractivesInterface.h"
#include "LocalPlayerPopupsSubsystem.h"

// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game startsHintInteractive
void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	//?? Refactor - used in proximityprompt ??
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Player controller not found"));
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Local player not found"));
		return;
	}

	LocalPlayerPopupsSubsystem = LocalPlayer->GetSubsystem<ULocalPlayerPopupsSubsystem>();
}
void UInteractiveComponent::HandleCurrentInteractiveType()
{
	UDocument* Document = nullptr;
	UHint* Hint = nullptr;

	if (LocalPlayerPopupsSubsystem)
	{
		Document = LocalPlayerPopupsSubsystem->GetPlayerDocumentPopup();
		Hint = LocalPlayerPopupsSubsystem->GetPlayerHintPopup();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: LocalPlayerPopupsSubsystem not found"));
		return;
	}

	switch (InteractiveType)
	{
	case EInteractiveType::IT_Default:
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Interactive type is default"));
		//check if GetOwner() is implementing IInteractiveInterface and call Interact_Implementation()
		if (GetOwner()->GetClass()->ImplementsInterface(UInteractivesInterface::StaticClass()))
		{
			IInteractivesInterface::Execute_Interact(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Owner does not implement IInteractiveInterface"));
		}

		break;
	case EInteractiveType::IT_Hint:
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Interactive type is Hint"));

		if (Hint->IsHintShown())
		{
			Hint->HideHint();
		}
		else
		{
			Hint->ShowHint(HintInfo);
		}

		break;
	case EInteractiveType::IT_Document:
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Interactive type is Document"));

		if (Document->IsDocumentShown())
		{
			Document->HideDocument();
		}
		else
		{
			Document->ShowDocument(DocumentInfo);
		}

		break;
	default:
		break;
	}
}


void UInteractiveComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	HandleCurrentInteractiveType();
}


void UInteractiveComponent::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Interactive implementation.."));

	HandleCurrentInteractiveType();
}

void UInteractiveComponent::SetEnabled(bool bEnabled)
{
	bIsEnabled = bEnabled;
}


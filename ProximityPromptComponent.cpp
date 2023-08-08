// Fill out your copyright notice in the Description page of Project Settings.


#include "ProximityPromptComponent.h"
#include "Components/WidgetComponent.h"
#include "MyMainCharacter.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "InteractiveComponent.h"
#include "InteractivesInterface.h"
#include "LocalPlayerPopupsSubsystem.h"
#include "Document.h"
#include "Hint.h"

UProximityPromptComponent::UProximityPromptComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(false);
}

void UProximityPromptComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Player controller not found"));
		return;
	}

	InteractiveComponent = GetOwner()->FindComponentByClass<UInteractiveComponent>();

	if (!InteractiveComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Interactive component not found"));
		return;
	}

	OnComponentBeginOverlap.AddDynamic(this, &UProximityPromptComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UProximityPromptComponent::OnOverlapEnd);
	PlayerController->OnPlayerInteractedDelegate.AddUObject(this, &UProximityPromptComponent::OnPlayerInteractPressed);

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractiveComponent: Local player not found"));
		return;
	}

	LocalPlayerPopupsSubsystem = LocalPlayer->GetSubsystem<ULocalPlayerPopupsSubsystem>();

}

void UProximityPromptComponent::StopUpdating()
{
	PrimaryComponentTick.SetTickFunctionEnable(false);
	bIsPlayerObserving = false;
	OnPlayerObservingEnd();
}

void UProximityPromptComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!InteractiveComponent->IsEnabled())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interactive component isn't enabled, returning.."));
		StopUpdating();
		return;
	}

	//Check if player is observing
	if (OverlappingCharacter == nullptr && bIsPlayerObserving)
	{
		UE_LOG(LogTemp, Warning, TEXT("Main character observing end"));
		StopUpdating();
		return;
	}
	else if (OverlappingCharacter == nullptr)
	{
		StopUpdating();
		return;
	}

	AActor* RaycastHit = OverlappingCharacter->CameraRaycast();

	if (!bIsPlayerObserving && RaycastHit == GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Main character observing begin"));
		bIsPlayerObserving = true;

		OnPlayerObservingStart();
	}
	else if (bIsPlayerObserving && RaycastHit != GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Main character observing end"));

		//create HideAll and refactor
		LocalPlayerPopupsSubsystem->GetPlayerDocumentPopup()->HideDocument();
		LocalPlayerPopupsSubsystem->GetPlayerHintPopup()->HideHint();

		StopUpdating();
	}
}

void UProximityPromptComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(AMyMainCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Main character overlap begin"));
		
		OverlappingCharacter = Cast<AMyMainCharacter>(OtherActor);
		PrimaryComponentTick.SetTickFunctionEnable(true);
	}
}

void UProximityPromptComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));

	OverlappingCharacter = nullptr;
}

void UProximityPromptComponent::OnPlayerInteractPressed()
{
	if (!InteractiveComponent->IsEnabled())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interactive component isn't enabled, returning.."));
		return;
	}

	if (OverlappingCharacter != nullptr && bIsPlayerObserving)
	{
		UE_LOG(LogTemp, Warning, TEXT("PPrompt: On player interacted"));

		TArray<UActorComponent*> InteractiveComponents = GetOwner()->GetComponentsByInterface(UInteractivesInterface::StaticClass());

		for (UActorComponent* ActorComponent : InteractiveComponents)
		{
			if (ActorComponent != this)
			{
				UE_LOG(LogTemp, Warning, TEXT("PPrompt: Found interactive interface, executing Interact"));
				IInteractivesInterface::Execute_Interact(ActorComponent);
			}
		}
	}
}

#if WITH_EDITOR
void UProximityPromptComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

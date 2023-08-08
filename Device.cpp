// Fill out your copyright notice in the Description page of Project Settings.


#include "Device.h"
#include "InteractiveComponent.h"
#include "GameplayDataSubsystem.h"


ADevice::ADevice()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	InteractiveComponent = CreateDefaultSubobject<UInteractiveComponent>(TEXT("InteractiveComponent"));
	InteractiveComponent->SetupAttachment(RootComponent);
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();

	GameplayDataSubsystem = GetGameInstance()->GetSubsystem<UGameplayDataSubsystem>();
}

void ADevice::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Device: Interact_Implementation"));
	if ( !IsItemRequired() || ( IsItemRequired() && GameplayDataSubsystem->PlayerOwnedItemIds.Contains(RequiredItemID)) )
	{
		if (!bIsEnabled)
		{
			bIsEnabled = true;
			OnEnabled();
		}
		else
		{
			bIsEnabled = false;
			OnDisabled();
		}

		if (!bIsReusable)
		{
			InteractiveComponent->SetEnabled(false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Device: Access denied"));
		OnAccessDenied();
	}
}

bool ADevice::IsItemRequired() const
{
	return (RequiredItemID != "" && RequiredItemID != "None");
}


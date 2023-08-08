// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "InteractiveComponent.h"
#include "GameplayDataSubsystem.h"

APickableItem::APickableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	//create defaultsubobejct of ItemMesh
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	//create defaultsubobejct of InteractiveComponent
	InteractiveComponent = CreateDefaultSubobject<UInteractiveComponent>(TEXT("InteractiveComponent"));
	InteractiveComponent->SetupAttachment(RootComponent);
}


void APickableItem::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Pickable item: Interact_Implementation"));

	GameplayDataSubsystem->PlayerOwnedItemIds.Add(ItemID);

	ItemMesh->SetVisibility(false);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	GameplayDataSubsystem = GetGameInstance()->GetSubsystem<UGameplayDataSubsystem>();
}


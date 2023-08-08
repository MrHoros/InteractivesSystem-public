// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractivesInterface.h"
#include "PickableItem.generated.h"

class UStaticMeshComponent;
class UInteractiveComponent;
class UGameplayDataSubsystem;

UCLASS()
class ACTIONADVENTURE_API APickableItem : public AActor, public IInteractivesInterface
{
	GENERATED_BODY()
	
public:	
	APickableItem();

	virtual void Interact_Implementation() override;


protected:
	virtual void BeginPlay() override;


private:
	UGameplayDataSubsystem* GameplayDataSubsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UInteractiveComponent* InteractiveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName ItemID;
};

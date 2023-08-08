// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractivesInterface.h"
#include "Device.generated.h"

class UStaticMeshComponent;
class UGameplayDataSubsystem;
class UInteractiveComponent;

UCLASS()
class ACTIONADVENTURE_API ADevice : public AActor, public IInteractivesInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevice();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnabled();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDisabled();

	UFUNCTION(BlueprintImplementableEvent)
	void OnAccessDenied();

public:	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactives")
	void Interact();
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintPure)
	bool IsEnabled() const { return bIsEnabled; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReusable = true;

private:
	UGameplayDataSubsystem* GameplayDataSubsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UInteractiveComponent* InteractiveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName RequiredItemID = "";

	bool IsItemRequired() const;

	bool bIsEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TArray<ADevice*> DevicesRequired;
};

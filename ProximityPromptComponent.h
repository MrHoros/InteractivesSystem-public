// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractivesInterface.h"
#include "ProximityPromptComponent.generated.h"

class UWidgetComponent;
class AMyMainCharacter;
class AMyPlayerController;
class ULocalPlayerPopupsSubsystem;
class UInteractiveComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UProximityPromptComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	UProximityPromptComponent();

protected:
	virtual void BeginPlay() override;

private:
	ULocalPlayerPopupsSubsystem* LocalPlayerPopupsSubsystem;

	AMyMainCharacter* OverlappingCharacter = nullptr;
	bool bIsPlayerObserving = false;

	AMyPlayerController* PlayerController = nullptr;

	UInteractiveComponent* InteractiveComponent = nullptr;

	void StopUpdating();

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerObservingStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerObservingEnd();

	UFUNCTION()
	void OnPlayerInteractPressed();

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif
};

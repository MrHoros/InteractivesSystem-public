#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayDataSubsystem.generated.h"

UCLASS()
class ACTIONADVENTURE_API UGameplayDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	TSet<FName> PlayerOwnedItemIds;
};

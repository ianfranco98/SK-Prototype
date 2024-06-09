#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SKGameMode.generated.h"

UCLASS(minimalapi)
class ASKGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void OnCharacterJumpOverObstacle(ACharacter* Character);

protected:

	UPROPERTY(EditDefaultsOnly, Category = GameRules)
	float PointsPerObstacle = 10.0f;
};




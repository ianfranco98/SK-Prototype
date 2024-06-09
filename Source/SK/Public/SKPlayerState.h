// //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SKPlayerState.generated.h"

DECLARE_DELEGATE_OneParam(FOnScoreUpdated, float NewScore);

UCLASS()
class SK_API ASKPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	virtual void OnRep_Score() override;

	FOnScoreUpdated OnScoreUpdated;

};

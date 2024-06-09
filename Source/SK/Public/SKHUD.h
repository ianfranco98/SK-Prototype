#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SKHUD.generated.h"

class USKScoreWidget;

UCLASS()
class SK_API ASKHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USKScoreWidget> ScoreWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<USKScoreWidget> ScoreWidget;
};

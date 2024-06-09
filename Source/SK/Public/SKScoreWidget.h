#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SKScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class SK_API USKScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void UpdateScore(float Score);

	UFUNCTION(BlueprintImplementableEvent)
	void OnScoreUpdated_Cosmetic(float NewScore);

protected:

	void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
};

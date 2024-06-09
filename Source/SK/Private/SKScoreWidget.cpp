#include "SKScoreWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/Pawn.h"
#include "SKPlayerState.h"

void USKScoreWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetOwningPlayerPawn()->GetPlayerState<ASKPlayerState>()->OnScoreUpdated.BindUObject(this, &USKScoreWidget::UpdateScore);
}

void USKScoreWidget::UpdateScore(float Score)
{
	ScoreText->SetText(FText::AsNumber(Score));

	OnScoreUpdated_Cosmetic(Score);
}


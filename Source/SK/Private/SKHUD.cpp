#include "SKHUD.h"
#include "SKScoreWidget.h"


void ASKHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<USKScoreWidget>(PlayerOwner.Get(), ScoreWidgetClass);
		ScoreWidget->AddToViewport();
	}
}
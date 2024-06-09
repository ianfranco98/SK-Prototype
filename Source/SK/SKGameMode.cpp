#include "SKGameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"


void ASKGameMode::OnCharacterJumpOverObstacle(ACharacter* Character)
{
	APlayerState* InstigatorPS = Character->GetPlayerState();
	const int NewScore = InstigatorPS->GetScore() + PointsPerObstacle;
	InstigatorPS->SetScore(NewScore);
	InstigatorPS->OnRep_Score();
}

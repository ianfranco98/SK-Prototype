#include "SKPlayerState.h"

void ASKPlayerState::OnRep_Score()
{
	OnScoreUpdated.ExecuteIfBound(GetScore());
}
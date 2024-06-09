#include "SKSpeedUpAnimNotify.h"
#include "SK/SKCharacter.h"

void USKSpeedUpAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ASKCharacter* SKCharacter = Cast<ASKCharacter>(MeshComp->GetOwner()))
	{
		SKCharacter->SpeedUp();
	}
}
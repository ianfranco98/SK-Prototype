#include "SKJumpAnimNotify.h"
#include "SK/SKCharacter.h"

void USKJumpAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ASKCharacter* SKCharacter = Cast<ASKCharacter>(MeshComp->GetOwner()))
	{
		SKCharacter->Jump();
	}
}
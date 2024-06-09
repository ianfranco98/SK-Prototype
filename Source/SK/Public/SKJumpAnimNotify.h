#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SKJumpAnimNotify.generated.h"


UCLASS()
class SK_API USKJumpAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};

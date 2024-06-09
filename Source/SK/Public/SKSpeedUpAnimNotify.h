#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SKSpeedUpAnimNotify.generated.h"


UCLASS()
class SK_API USKSpeedUpAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SKObstacleDetectionComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class SK_API USKObstacleDetectionComponent : public UBoxComponent
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	void OnCharacterJumping(bool bIsCharacterJumping);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(Transient)
	TArray<AActor*> ActorsToCheck;

	bool bIsCheckingForObstacles = false;
};

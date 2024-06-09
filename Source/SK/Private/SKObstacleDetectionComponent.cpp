#include "SKObstacleDetectionComponent.h"
#include "SK/SKCharacter.h"
#include "SK/SKGameMode.h"

void USKObstacleDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ASKCharacter* Character = Cast<ASKCharacter>(GetOwner()))
	{
		Character->OnCharacterIsJumping.AddUObject(this, &USKObstacleDetectionComponent::OnCharacterJumping);
	}

	OnComponentBeginOverlap.AddUniqueDynamic(this, &USKObstacleDetectionComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddUniqueDynamic(this, &USKObstacleDetectionComponent::OnEndOverlap);
}

void USKObstacleDetectionComponent::OnCharacterJumping(bool bIsCharacterJumping)
{
	bIsCheckingForObstacles = bIsCharacterJumping;

	if (!bIsCheckingForObstacles)
	{
		ActorsToCheck.Empty();
	}
}

void USKObstacleDetectionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsCheckingForObstacles)
	{
		ActorsToCheck.AddUnique(OtherActor);
	}
}

void USKObstacleDetectionComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bool bActorFound = ActorsToCheck.Find(OtherActor) != INDEX_NONE;
	if (bIsCheckingForObstacles && bActorFound)
	{
		if (ASKGameMode* GameMode = Cast<ASKGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnCharacterJumpOverObstacle(Cast<ACharacter>(GetOwner()));
		}
		 
		ActorsToCheck.Remove(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is an obstacle!"), *OtherActor->GetName());
	}

}

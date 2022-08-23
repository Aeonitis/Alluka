#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    // Register Actor frame tick/updates
    PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Server-side Logic
    if (HasAuthority())
    {
        FVector ActorLocation = GetActorLocation();

        // Translated location from Local (relative) location to global (world)
        FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
        // Normalized direction vector to target
        FVector DirectionToTarget = (GlobalTargetLocation - ActorLocation).GetSafeNormal();

        // Increment location towards Normalized Direction (DirectionToTarget) multiplied in magnitude of (Speed * Deltatime)
        ActorLocation += DirectionToTarget * (MovementSpeed * DeltaTime);
        SetActorLocation(ActorLocation);
    }
}

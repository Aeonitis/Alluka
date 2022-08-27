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

    // Initial spawn location
    GlobalStartLocation = GetActorLocation();

    // Translated location from Local (relative) location to global (world)
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Server-side Logic
    if (HasAuthority())
    {
        FVector ActorLocation = GetActorLocation();

        // Normalized direction vector to target
        FVector DirectionToTarget = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

        // Increment location towards Normalized Direction (DirectionToTarget) multiplied in magnitude of (Speed * Deltatime)
        ActorLocation += DirectionToTarget * (MovementSpeed * DeltaTime);
        SetActorLocation(ActorLocation);
    }
}

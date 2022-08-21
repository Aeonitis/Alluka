#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    // Register Actor frame tick/updates
    PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    // Server-side Logic
    if (HasAuthority())
    {
        FVector ActorLocation = GetActorLocation();

        // Increment location in cm
        ActorLocation += FVector(MovementSpeed * DeltaTime, 0, 0);
        SetActorLocation(ActorLocation);
    }
}

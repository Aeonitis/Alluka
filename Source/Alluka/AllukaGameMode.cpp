// Copyright Epic Games, Inc. All Rights Reserved.

#include "AllukaGameMode.h"
#include "AllukaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAllukaGameMode::AAllukaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

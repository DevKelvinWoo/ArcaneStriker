// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcaneStrikerGameMode.h"
#include "ArcaneStrikerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArcaneStrikerGameMode::AArcaneStrikerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

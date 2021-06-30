// Copyright Epic Games, Inc. All Rights Reserved.

#include "Simple_PlatformerGameMode.h"
#include "Simple_PlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASimple_PlatformerGameMode::ASimple_PlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

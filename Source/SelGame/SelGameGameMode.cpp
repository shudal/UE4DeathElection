// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelGameGameMode.h"
#include "SelGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASelGameGameMode::ASelGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

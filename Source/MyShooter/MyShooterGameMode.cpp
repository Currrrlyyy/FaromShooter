// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyShooterGameMode.h"
#include "MyShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyShooterGameMode::AMyShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

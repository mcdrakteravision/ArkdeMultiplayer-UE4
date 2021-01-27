// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArkdeCMGameMode.h"
#include "ArkdeCMCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ACM_PlayerController.h"
#include "ACM_GameState.h"

AArkdeCMGameMode::AArkdeCMGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

//===============================================================================================================
void AArkdeCMGameMode::PlayerKilled(AController* VictimController)
{
	AACM_PlayerController* ArkdeVictimController = Cast<AACM_PlayerController>(VictimController);
	if (IsValid(ArkdeVictimController))
	{
		ArkdeVictimController->GameConclussion(false);
	}

	AACM_GameState* WorldGameState = GetWorld()->GetGameState<AACM_GameState>();
	if (IsValid(WorldGameState))
	{
		WorldGameState->CheckWinCondition();
	}
}

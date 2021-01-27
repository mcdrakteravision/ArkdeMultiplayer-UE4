// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_GameState.h"
#include "ACM_PlayerController.h"
#include "ACM_PlayerState.h"

void AACM_GameState::CheckWinCondition()
{
	int AlivePlayersCounter = 0;
	AACM_PlayerController* WinningPlayerController = nullptr;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AACM_PlayerController* PlayerController = Cast<AACM_PlayerController>(It->Get());
		if (IsValid(PlayerController))
		{
			AACM_PlayerState* PlayerState = PlayerController->GetPlayerState<AACM_PlayerState>();
			if (IsValid(PlayerState))
			{
				if (PlayerState->IsAlive())
				{
					AlivePlayersCounter++;

					if (AlivePlayersCounter > 1)
					{
						return;
					}
					else
					{
						WinningPlayerController = PlayerController;
					}
				}
			}
		}
	}

	WinningPlayerController->GameConclussion(true);
}

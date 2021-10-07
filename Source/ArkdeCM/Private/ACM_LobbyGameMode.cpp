// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_LobbyGameMode.h"

//===============================================================================================================
AACM_LobbyGameMode::AACM_LobbyGameMode()
{
	MaxAmountOfPlayersToTravel = 2;
	CurrentPlayersOnLobby = 0;
}

//===============================================================================================================
void AACM_LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (IsValid(NewPlayer))
	{
		CurrentPlayersOnLobby++;

		if (CurrentPlayersOnLobby >= MaxAmountOfPlayersToTravel)
		{
			UWorld* GameWorld = GetWorld();
			if (IsValid(GetWorld()))
			{
				bUseSeamlessTravel = true;
				GameWorld->ServerTravel("/Game/Maps/BattleRoyaleMap?listen");
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_GameInstance.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include <Interfaces/OnlineSessionInterface.h>

void UACM_GameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::Init Subsytem Found %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::Init Session Interface Found"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UACM_GameInstance::OnSessionCreated);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UACM_GameInstance::OnSessionDestroyed);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UACM_GameInstance::OnSessionsFound);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UACM_GameInstance::OnSessionJoined);
		}
	}

}

void UACM_GameInstance::Host()
{
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::Host Create session start"));
	auto CreatedSession = SessionInterface->GetNamedSession(SessionDefaultName);
	if (CreatedSession)
	{
		SessionInterface->DestroySession(SessionDefaultName);
	}
	else
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.NumPublicConnections = 2;
		SessionInterface->CreateSession(0, SessionDefaultName, SessionSettings);
	}
}

void UACM_GameInstance::Join()
{
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::Join Find Sessions Start"));
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100;
	SessionSearch->bIsLanQuery =true;
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UACM_GameInstance::OnSessionCreated(FName SessionName, bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionCreated Create session end"));
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionCreated Create session failed"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionCreated Create session success"));
	UWorld* GameWorld = GetWorld();
	GameWorld->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UACM_GameInstance::OnSessionDestroyed(FName SessionName, bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionDestroyed Destroy session end"));
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionDestroyed Destroy session failed"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionDestroyed destroy session success"));
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 2;
	SessionInterface->CreateSession(0, SessionDefaultName, SessionSettings);
}

void UACM_GameInstance::OnSessionsFound(bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionsFound Find Sessions end"));
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionsFound Find Sessions failed"));
		return;
	}

	if (SessionSearch->SearchResults.Num() > 0)
	{
		for (FOnlineSessionSearchResult CurrentResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionsFound Session Found %s"), *CurrentResult.GetSessionIdStr());
		}
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionsFound Join Session start"));
		SessionInterface->JoinSession(0, SessionDefaultName, SessionSearch->SearchResults[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionsFound No Sessions found"));
	}
}

void UACM_GameInstance::OnSessionJoined(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionJoined Join Sessions end"));
	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionJoined Join Sessions failed"));
		return;
	}
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACM_GameInstance::OnSessionJoined No player controller found"));
		return;
	}
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

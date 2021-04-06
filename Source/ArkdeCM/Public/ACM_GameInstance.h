// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <../../../Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h>
#include <UObject/NameTypes.h>
#include <OnlineSessionSettings.h>
#include <Templates/SharedPointer.h>
#include <Interfaces/OnlineSessionInterface.h>
#include "ACM_GameInstance.generated.h"



/**
 * 
 */
UCLASS()
class ARKDECM_API UACM_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FName SessionDefaultName = TEXT("SessionName");

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void Host();

	UFUNCTION(BlueprintCallable)
	void Join();

	void OnSessionCreated(FName SessionName, bool Success);

	void OnSessionDestroyed(FName SessionName, bool Success);
	
	void OnSessionsFound(bool Success);

	void OnSessionJoined(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
};

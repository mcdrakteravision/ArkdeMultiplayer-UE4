// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ACM_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARKDECM_API AACM_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* aPawn) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GameConclussion(bool WasSuccesful);

	void GameConclussion(bool WasSuccesful);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ViewActorClass;
};

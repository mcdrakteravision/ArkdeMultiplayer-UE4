// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkdeCMGameMode.generated.h"

class APlayerStart;
class AACM_Collectable;

UCLASS(minimalapi)
class AArkdeCMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArkdeCMGameMode();

	void PlayerKilled(AController* VictimController);
	
	virtual void BeginPlay() override;

	TArray<APlayerStart*> WorldPlayerStarts;

	void InitPlayerStarts();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AACM_Collectable>> SpawnableCollectables;

	void SetupWorldSpawners();
};




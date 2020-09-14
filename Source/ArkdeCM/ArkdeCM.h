// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EACM_AbilityInputID : uint8
{
	// 0 None
	None UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel UMETA(DisplayName = "Cancel"),
	// 3 Ability1
	Ability1 UMETA(DisplayName = "Ability1"),
	// 4 Ability2
	Ability2 UMETA(DisplayName = "Ability2"),
	// 5 Sprint
	Sprint UMETA(DisplayName = "Sprint"),
	// 6 Jump
	Jump UMETA(DisplayName = "Jump"),
};
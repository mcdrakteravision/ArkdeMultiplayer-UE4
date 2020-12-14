// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_PlayerState.h"
#include "AbilitySystemComponent.h"
#include "ACM_AttributeSet.h"
#include "ArkdeCM/ArkdeCMCharacter.h"

//===============================================================================================================
AACM_PlayerState::AACM_PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));;
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UACM_AttributeSet>(TEXT("Attribute Set"));

	NetUpdateFrequency = 100.f;
}

//===============================================================================================================
UAbilitySystemComponent* AACM_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

//===============================================================================================================
UACM_AttributeSet* AACM_PlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

//===============================================================================================================
bool AACM_PlayerState::IsAlive() const
{
	return GetHealth() > 0.f;
}

//===============================================================================================================
float AACM_PlayerState::GetHealth() const
{
	return GetAttributeSet()->GetHealth();
}

//===============================================================================================================
float AACM_PlayerState::GetMaxHealth() const
{
	return GetAttributeSet()->GetMaxHealth();
}

//===============================================================================================================
float AACM_PlayerState::GetHealthRegen() const
{
	return GetAttributeSet()->GetHealthRegen();
}

//===============================================================================================================
void AACM_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent))
	{
		// Callback Attribute Change
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &AACM_PlayerState::OnHealthChanged);
	}
}

//===============================================================================================================
void AACM_PlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (!IsAlive() && IsValid(AbilitySystemComponent))
	{
		AArkdeCMCharacter* characterRef = Cast<AArkdeCMCharacter>(GetPawn());
		if (IsValid(characterRef))
		{
			characterRef->Die();
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ArkdeCM/ArkdeCMCharacter.h"

//===============================================================================================================
// Sets default values
AACM_Projectile::AACM_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
}

//===============================================================================================================
void AACM_Projectile::Multicast_IgnoreActor_Implementation(AArkdeCMCharacter* ActorToIgnore)
{
	SphereComponent->IgnoreActorWhenMoving(ActorToIgnore, true);
}

//===============================================================================================================
bool AACM_Projectile::Multicast_IgnoreActor_Validate(AArkdeCMCharacter* ActorToIgnore)
{
	return true;
}

//===============================================================================================================
// Called when the game starts or when spawned
void AACM_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

//===============================================================================================================
// Called every frame
void AACM_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


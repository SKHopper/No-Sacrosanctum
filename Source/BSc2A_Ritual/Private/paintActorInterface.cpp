// Fill out your copyright notice in the Description page of Project Settings.


#include "paintActorInterface.h"
#include "spellProjectile.h"

// Sets default values
ApaintActorInterface::ApaintActorInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TArray<int32> ApaintActorInterface::getPattern_Implementation() {
	return TArray<int32>();
}

void ApaintActorInterface::doSpellSprite_Implementation(EspellType type) {}

TArray<int32> ApaintActorInterface::endPainting()
{
	stopPainting();
	TArray<int32> pattern = getPattern();
	return getPattern();
}

void ApaintActorInterface::setPlayer(AActor* inPlayer) {
	player = inPlayer;
}

void ApaintActorInterface::initialize(AActor* inPlayer) {

	if (inPlayer) {

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParams.Name = FName(*FString::Printf(TEXT("Spell Projectile")));
		spawnParams.Owner = inPlayer;

		spellProjectile = GetWorld()->SpawnActor<AspellProjectile>(
			BP_spellClass,
			inPlayer->GetActorLocation(),
			FRotator::ZeroRotator,
			spawnParams
		);

	}

	if (spellProjectile) {
		spellProjectile->setPlayer(inPlayer);
		initializeBP();
	}
}

// Called when the game starts or when spawned
void ApaintActorInterface::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ApaintActorInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


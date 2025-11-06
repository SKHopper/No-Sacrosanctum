// Fill out your copyright notice in the Description page of Project Settings.


#include "spellProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
AspellProjectile::AspellProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(collider);
}

// Called when the game starts or when spawned
void AspellProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AspellProjectile::setPlayer(AActor* inPlayer) {
	player = inPlayer;
}

// Called every frame
void AspellProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorRotation(
		UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation())
	);
}


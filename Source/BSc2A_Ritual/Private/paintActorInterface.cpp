// Fill out your copyright notice in the Description page of Project Settings.


#include "paintActorInterface.h"

// Sets default values
ApaintActorInterface::ApaintActorInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<int32> ApaintActorInterface::getPattern_Implementation() {
	return TArray<int32>();
}

TArray<int32> ApaintActorInterface::endPainting()
{
	stopPainting();
	return getPattern();
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


// Fill out your copyright notice in the Description page of Project Settings.


#include "testCppActor.h"

// Sets default values
AtestCppActor::AtestCppActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	testMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test Mesh"));
	testMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AtestCppActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		timerHandle,
		this,
		&AtestCppActor::swapMaterial,
		1.0f,
		true,
		.4f
	);
}

void AtestCppActor::swapMaterial() {
	if (testMesh->GetMaterial(0) == testMaterial1) {
		testMesh->SetMaterial(0, testMaterial2);
	}
	else {
		testMesh->SetMaterial(0, testMaterial1);
	}
}
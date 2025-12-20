// Fill out your copyright notice in the Description page of Project Settings.


#include "floodSource.h"
#include "streamBPComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AfloodSource::AfloodSource()
{
	spellType = EspellType::source;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	collider->SetupAttachment(RootComponent);

	if (mesh) {
		mesh->SetVisibility(false);
	}

}

// Called when the game starts or when spawned
void AfloodSource::BeginPlay()
{
	Super::BeginPlay();

	if (bodyActor) {
		parentBody = Cast<IfloodIF>(bodyActor);
		queueRandomBegin();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("floodSource '%s' has no bodyActor"), *GetNameSafe(this));
	}
}

void AfloodSource::queueRandomBegin() {
	GetWorld()->GetTimerManager().SetTimer(
		beginTimer,
		this,
		&AfloodSource::beginLeak,
		FMath::RandRange(minBeginTime, maxBeginTime),
		false
	);
}

void AfloodSource::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AfloodSource::beginLeak() {

	isLeaking = true;
	mesh->SetVisibility(true);
	floodStream->start();
	parentBody->changeLeakRate(leakRate);
}

void AfloodSource::endLeak() {

	isLeaking = false;
	mesh->SetVisibility(false);
	floodStream->end();
	parentBody->changeLeakRate(-leakRate);
	queueRandomBegin();
}

void AfloodSource::getSpelled() {

	if (isLeaking) {
		endLeak();
	}
}


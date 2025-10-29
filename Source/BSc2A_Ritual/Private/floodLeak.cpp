// Fill out your copyright notice in the Description page of Project Settings.


#include "floodLeak.h"
#include "Components/BoxComponent.h"

// Sets default values
AfloodLeak::AfloodLeak()
{
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

void AfloodLeak::beginLeaking() {
	leakHeight = FMath::RandRange(minSpawnHeight, maxSpawnHeight);
	SetActorLocation(GetActorLocation() + FVector(0, 0, leakHeight));

	canLeak = true;
	isUpdating = false;
	mesh->SetVisibility(true);
	updateLeak();

}

void AfloodLeak::queueRandomBegin() {
	GetWorld()->GetTimerManager().SetTimer(
		beginTimer,
		this,
		&AfloodLeak::beginLeaking,
		FMath::RandRange(minBeginTime, maxBeginTime),
		false
	);
}

// Called when the game starts or when spawned
void AfloodLeak::BeginPlay()
{
	Super::BeginPlay();

	if (bodyActors.Num()) {

		parentBodies.Add(Cast<IfloodIF>(bodyActors[0]));
		parentBodies.Add(Cast<IfloodIF>(bodyActors[1]));
		parentBodies[0]->conveyLeakActor(this, leakHeight);
		parentBodies[1]->conveyLeakActor(this, leakHeight);

		queueRandomBegin();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("floodLeak '%s' has no parentBodies"), *GetNameSafe(this));
	}

}

void AfloodLeak::stopLeak(int bodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("STOPPING LEAK"));
	isLeaking = false;
	parentBodies[bodyIndex]->changeLeakRate(-bodyLeakRates[bodyIndex]);
	bodyLeakRates[bodyIndex] = 0;
}

void AfloodLeak::setOneWay(int bodyIndex, TArray<double>& bodyHeights) {
	UE_LOG(LogTemp, Warning, TEXT("setting one way leak"), bodyHeights[0], bodyHeights[1]);
	
	isLeaking = true;

	int altIndex = 1 - bodyIndex;
		
	//set leaking higher body leak rate relative zero, set leaking higher body leak rate to negative leak rate
	parentBodies[bodyIndex]->changeLeakRate(-bodyLeakRates[bodyIndex] - leakRate);
	//update documentation
	bodyLeakRates[bodyIndex] = -leakRate;

	parentBodies[altIndex]->changeLeakRate(-bodyLeakRates[altIndex] + leakRate);
	bodyLeakRates[altIndex] = leakRate;
}

/*
* 
* assume time now is zero
* 
* y = m*x + c
* future height = rate(future time) + current height
* 
* y = m1*x + c1
* y = m2*x + c2
* 
* m1*x + c1 = m2*x + c2
* 
* rate line intersect = x = (c2 - c1) / (m1 - m2) = future time
* 
*/
double AfloodLeak::predictUnlevelTime(TArray<double>& bodyHeights) {

	double c1 = bodyHeights[0];
	double c2 = bodyHeights[1];
	double m1 = parentBodies[1]->getTotalRate();
	double m2 = parentBodies[0]->getTotalRate();

	if (m1 - m2 == 0) return 1;

	return (c2 - c1) / (m1 - m2);
}

void AfloodLeak::updateLeak() {

	//TODO: simplify below

	if (canLeak) {

		if (not hasUpdatedThisTick) {
			hasUpdatedThisTick = true;

			TArray<double> bodyHeights = { parentBodies[0]->getBodyHeight(), parentBodies[1]->getBodyHeight() };

			//TODO: levelize extremely similar heights with exactly similar rates

			UE_LOG(LogTemp, Warning, TEXT("height A %f, height B %f"), bodyHeights[0], bodyHeights[1]);

			
			if (
				abs(bodyHeights[0] - bodyHeights[1]) < levelizeBodiesThreshold 
				or not (
					bodyHeights[0] > leakHeight 
					or bodyHeights[1] > leakHeight
				)
			) {
				UE_LOG(LogTemp, Warning, TEXT("setting no leak"));
				isLeaking = false;
				parentBodies[0]->changeLeakRate(-bodyLeakRates[0]);
				parentBodies[1]->changeLeakRate(-bodyLeakRates[1]);
				bodyLeakRates = { 0, 0 };
			}
			else if (bodyHeights[0] > bodyHeights[1]) { //"Normal" flow direction

				if (not isLeaking or (isLeaking and isLeakingAlt)) {
					setOneWay(0, bodyHeights);
					isLeakingAlt = false;
				}
			}
			else if (bodyHeights[0] < bodyHeights[1]) { //"Alt" flow direction

				if (not isLeaking or (isLeaking and not isLeakingAlt)) {
					setOneWay(1, bodyHeights);
					isLeakingAlt = true;
				}
			}

			/*
			GetWorld()->GetTimerManager().SetTimer(
				updateTimer,
				this,
				&AfloodLeak::updateLeak,
				predictUnlevelTime(bodyHeights),
				false
			);
			*/
		}
		
	}
	else {
		stopLeak(0);
		stopLeak(1);
	}

}

// Called every frame
void AfloodLeak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	hasUpdatedThisTick = false;
}

void AfloodLeak::suggestLeakUpdate() {

	if (isUpdating) return;
	isUpdating = true;
	updateLeak();
	isUpdating = false;
}

void AfloodLeak::interact(bool alternate) {

	if (canLeak) {
		endLeak();
	}
}

void AfloodLeak::endLeak() {

	canLeak = false;
	isUpdating = false;
	hasUpdatedThisTick = false;
	mesh->SetVisibility(false);
	updateLeak();
	queueRandomBegin();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "floodLeak.h"
#include "streamBPComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AfloodLeak::AfloodLeak()
{
	spellType = EspellType::leak;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(root);

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	collider->SetupAttachment(RootComponent);
	leftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Left"));
	leftMesh->SetupAttachment(RootComponent);
	rightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Right"));
	rightMesh->SetupAttachment(RootComponent);

}

void AfloodLeak::beginLeaking() {
	
	leakHeight = FMath::RandRange(minSpawnHeight, maxSpawnHeight);
	SetActorLocation(GetActorLocation() + FVector(0, 0, leakHeight));

	FVector lV = floodStreamLeft->GetComponentLocation();
	FVector rV = floodStreamRight->GetComponentLocation();
	floodStreamLeft->SetWorldLocation({ lV.X, lV.Z, GetActorLocation().Z });
	floodStreamRight->SetWorldLocation({ rV.X, rV.Z, GetActorLocation().Z });

	canLeak = true;
	isUpdating = false;
	leftMesh->SetVisibility(true);
	rightMesh->SetVisibility(true);
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
		//UE_LOG(LogTemp, Warning, TEXT("floodLeak '%s' has no parentBodies"), *GetNameSafe(this));
	}

}

void AfloodLeak::changeLeak(double index, double delta) {
	parentBodies[index]->changeLeakRate(delta);
	bodyLeakRates[index] = bodyLeakRates[index] + delta;
	UstreamBPComponent* stream = index ? floodStreamRight : floodStreamLeft;
	if (bodyLeakRates[index] > 0) {
		stream->start();
	}
	else {
		stream->end();
	}
}

void AfloodLeak::setNoLeak() {
	//UE_LOG(LogTemp, Warning, TEXT("setting no leak"));
	isLeaking = false;
	changeLeak(0, -bodyLeakRates[0]);
	changeLeak(1, -bodyLeakRates[1]);
}

void AfloodLeak::setOneWay(int bodyIndex, TArray<double>& bodyHeights) {

	isLeakingAlt = bool(bodyIndex);
	//UE_LOG(LogTemp, Warning, TEXT("setting one way leak"), bodyHeights[0], bodyHeights[1]);
	isLeaking = true;

	int altIndex = 1 - bodyIndex;
		
	setNoLeak();

	//set leaking higher body leak rate to negative leak rate
	changeLeak(bodyIndex, -leakRate);
	changeLeak(altIndex, leakRate);
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

bool AfloodLeak::noNeedForLeakage(TArray<double>& bodyHeights) {
	return 
		abs(bodyHeights[0] - bodyHeights[1]) < levelizeBodiesThreshold 
		or not (bodyHeights[0] > leakHeight or bodyHeights[1] > leakHeight);
}

void AfloodLeak::updateLeak() {

	if (not canLeak) {
		setNoLeak();
		return;
	}

	if (not hasUpdatedThisTick) {

		hasUpdatedThisTick = true;
		TArray<double> bodyHeights = { parentBodies[0]->getBodyHeight(), parentBodies[1]->getBodyHeight() };

		//TODO: levelize extremely similar heights with exactly similar rates
		//UE_LOG(LogTemp, Warning, TEXT("height A %f, height B %f"), bodyHeights[0], bodyHeights[1]);

		if (noNeedForLeakage(bodyHeights)) {
			setNoLeak();
		}
		else if (
			bodyHeights[0] > bodyHeights[1]//should be "normal" flow
			and
			(not isLeaking or (isLeaking and isLeakingAlt))//is not "normal" flow
		) {
			setOneWay(0, bodyHeights);
		}
		else if (
			bodyHeights[0] < bodyHeights[1]//should be "alt" flow
			and
			(not isLeaking or (isLeaking and not isLeakingAlt))//should be "alt" flow
		) {
			setOneWay(1, bodyHeights);
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

void AfloodLeak::getSpelled() {

	if (canLeak) {
		endLeak();
	}
}

void AfloodLeak::endLeak() {

	SetActorLocation(GetActorLocation() - FVector(0, 0, leakHeight));
	leakHeight = 0;

	leftMesh->SetVisibility(false);
	rightMesh->SetVisibility(false);

	canLeak = false;
	isUpdating = false;
	hasUpdatedThisTick = false;
	updateLeak();
	
	queueRandomBegin();
}

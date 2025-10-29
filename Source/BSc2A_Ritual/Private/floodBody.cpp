


#include "floodBody.h"
#include "Components/BoxComponent.h"


// Sets default values
AfloodBody::AfloodBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	bodyMesh->SetupAttachment(RootComponent);
	
	bodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Body Collider"));
	bodyCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AfloodBody::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();
	
}

bool AfloodBody::isBodyDry() {
	return false;
}

double AfloodBody::getHeight() {
	return floodHeight;
}

void AfloodBody::updateFloodLevel(float DeltaTime) {

	FVector newLocation = startLocation;
	double newZ = GetActorLocation().Z;
	newZ = FMath::Clamp(newZ + leakRateTotal * DeltaTime, startLocation.Z, startLocation.Z + maxHeight);
	floodHeight = newZ - startLocation.Z;
	newLocation.Z = newZ;
	SetActorLocation(newLocation);

	TArray<double> heights;
	heightLeaks.GetKeys(heights);

	for (double height : heights) {
		if (floodHeight >= height) {
			for (IfloodIF* leak : *heightLeaks.Find(height)) {
				leak->suggestLeakUpdate();
			}
		}
		
	}

	/*
	* 
	* TODO:
	* 
	* if height changes between states of [zero, middling, maximum]:
	* suggest leak updates
	* 
	*/
}

// Called every frame
void AfloodBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (leakRateTotal) {

		updateFloodLevel(DeltaTime);

	}

}

void AfloodBody::changeLeakRate(double change) {

	leakRateTotal += change;

	UE_LOG(LogTemp, Warning, TEXT("%s: RATE to %f, CHANGE of %f"), *GetNameSafe(this), leakRateTotal, change);

	for (IfloodIF* leak : leaks) {
		leak->suggestLeakUpdate();
	}
}

void AfloodBody::conveyLeakActor(AActor* leak, double leakHeight) {
	IfloodIF* castedLeak = Cast<IfloodIF>(leak);
	leaks.Add(castedLeak);
	if (heightLeaks.Contains(leakHeight)) {
		heightLeaks.Find(leakHeight)->Add(castedLeak);
	}
	else {
		heightLeaks.Add(leakHeight, { castedLeak });
	}
}

double AfloodBody::getBodyHeight() {
	return getHeight();
};

double AfloodBody::getTotalRate() {
	return leakRateTotal;
}




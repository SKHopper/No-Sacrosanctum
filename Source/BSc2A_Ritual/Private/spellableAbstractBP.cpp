


#include "spellableAbstractBP.h"


// Sets default values
AspellableAbstractBP::AspellableAbstractBP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AspellableAbstractBP::getSpelled() {
	onSpelled();
}

// Called when the game starts or when spawned
void AspellableAbstractBP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AspellableAbstractBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



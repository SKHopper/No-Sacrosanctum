


#include "spellable.h"


// Sets default values
Aspellable::Aspellable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

EspellType Aspellable::getSpellType()
{
	return spellType;
}

// Called when the game starts or when spawned
void Aspellable::BeginPlay()
{
	Super::BeginPlay();
	
}

bool Aspellable::trySpell(EspellType key) {
	bool worked = key == spellType;

	if (worked) {
		//C++
		getSpelled();
		//UE5BP
		onSpelled();
	}

	return worked;
}

// Called every frame
void Aspellable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



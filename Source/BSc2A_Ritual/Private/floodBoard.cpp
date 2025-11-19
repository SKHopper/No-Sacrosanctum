


#include "floodBoard.h"
#include "Components/BoxComponent.h"


// Sets default values
AfloodBoard::AfloodBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spellCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Spell Collider"));
	generalCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("General Collider"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(spellCollider);
	generalCollider->SetupAttachment(spellCollider);
	mesh->SetupAttachment(spellCollider);
}

// Called when the game starts or when spawned
void AfloodBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AfloodBoard::getSpelled() {

	if (notBoardedUp) {

		notBoardedUp = false;
		boardUpEffect();
	}
}

// Called every frame
void AfloodBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



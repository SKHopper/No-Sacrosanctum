


#include "floodBoard.h"
#include "Components/BoxComponent.h"


// Sets default values
AfloodBoard::AfloodBoard()
{
	spellType = EspellType::boardUp;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	spellCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Spell Collider"));
	generalCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("General Collider"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(root);
	spellCollider->SetupAttachment(GetRootComponent());
	generalCollider->SetupAttachment(GetRootComponent());
	mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AfloodBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AfloodBoard::bodyFilled() {

	if (notBoardedUp) {
		gameState->bodyFilled();
	}
}

void AfloodBoard::conveyGameState(IfloodIF* gameStateIF) {
	gameState = gameStateIF;
}

void AfloodBoard::getSpelled() {

	if (notBoardedUp) {
		notBoardedUp = false;

		spellCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		boardUpEffect();
	}
}

// Called every frame
void AfloodBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



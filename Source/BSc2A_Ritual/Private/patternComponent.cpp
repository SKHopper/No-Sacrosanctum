


#include "patternComponent.h"
#include "BSc2A_RitualCharacter.h"
#include "paintActorInterface.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UpatternComponent::UpatternComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	paintActor = CreateDefaultSubobject<ApaintActorInterface>("Paint Actor");
	UWorld* world = GetWorld();
	if (world) {
		player = Cast<ABSc2A_RitualCharacter>(UGameplayStatics::GetPlayerCharacter(world, 0));
	}
}


// Called when the game starts
void UpatternComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UpatternComponent::openMenu() {
	paintActor->beginPainting();
}

void UpatternComponent::closeMenu() {
	TArray<int32> test = paintActor->endPainting();
	for (int32 num : test) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, FString::Printf(TEXT("'%d'"), num));
	}
}


// Called every frame
void UpatternComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



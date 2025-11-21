


#include "patternComponent.h"
#include "BSc2A_RitualCharacter.h"
#include "Camera/CameraComponent.h"
#include "paintActorInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UpatternComponent::UpatternComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	paintActor = CreateDefaultSubobject<ApaintActorInterface>("Paint Actor");
}


// Called when the game starts
void UpatternComponent::BeginPlay()
{
	Super::BeginPlay();

	spellIDs = spellPatternsTable->GetRowNames();
}

void UpatternComponent::initialize(ABSc2A_RitualCharacter* inPlayer) {
	player = inPlayer;
	paintActor->initialize(Cast<AActor>(player));
}

void UpatternComponent::endSpellcasting() {
	FString pattern;

	TArray<int32> outPattern = closeMenu();
	for (int32 vertex : outPattern) {
		pattern.AppendInt(vertex);
	}

	if (spellPatternsTable != nullptr) {

		bool validSpell = false;
		FspellPattern* spellPattern;
		for (FName spellID : spellIDs) {

			spellPattern = spellPatternsTable->FindRow<FspellPattern>(spellID, "");
			if (pattern == spellPattern->pattern) {
				validSpell = true;
				paintActor->doSpellSprite(spellPattern->spellType);
				break;
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("table is null"));
	}
}

TArray<int32> UpatternComponent::closeMenu() {
	inMenu = false;
	TArray<int32> outPattern = paintActor->endPainting();
	return outPattern;
}

//TODO: make sure spelless menu exit sets right boolean trackers
bool UpatternComponent::toggleSpell() {
	bool openedMenu = false;

	if (paintActor->getSpellSpriteActive()) {

		if (paintActor->getSpellSpriteIdle()) {//end idle, start launch

			paintActor->startLaunchSpell(player->GetFirstPersonCameraComponent()->GetForwardVector());
		}
		//else:
		//	  player attempted to open menu with spell mid-launch, input ignored
	}
	else if (inMenu) {//end menu, start idle
		endSpellcasting();
	}
	else {//start menu
		openedMenu = inMenu = true;
		paintActor->beginPainting();
	}

	return openedMenu;
}


// Called every frame
void UpatternComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



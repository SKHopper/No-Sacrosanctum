


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

	paintActor = CreateDefaultSubobject<ApaintActorInterface>("Paint Actor");
}


// Called when the game starts
void UpatternComponent::BeginPlay()
{
	Super::BeginPlay();

	spellIDs = spellPatternsTable->GetRowNames();
}

void UpatternComponent::openMenu() {
	paintActor->beginPainting();
}

void UpatternComponent::doSpell(EspellType spell) {

	switch (spell) {

	case EspellType::source:
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, FString::Printf(TEXT("SOURCE SPELL")));
		break;

	case EspellType::leak:
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, FString::Printf(TEXT("LEAK SPELL")));
		break;

	case EspellType::boardUp:
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, FString::Printf(TEXT("BOARD SPELL")));
		break;

	default:
		return;
	}

	paintActor->doSpellSprite(spell);
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
	GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, pattern);


	if (spellPatternsTable != nullptr) {

		bool validSpell = false;
		FspellPattern* spellPattern;
		for (FName spellID : spellIDs) {

			spellPattern = spellPatternsTable->FindRow<FspellPattern>(spellID, "");
			if (pattern == spellPattern->pattern) {
				validSpell = true;
				doSpell(spellPattern->spellType);
				break;
			}
		}

		if (not validSpell) {
			GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, FString::Printf(TEXT("NO SPELL")));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("table is null"));
	}
}

TArray<int32> UpatternComponent::closeMenu() {
	TArray<int32> outPattern = paintActor->endPainting();
	return outPattern;
}


// Called every frame
void UpatternComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



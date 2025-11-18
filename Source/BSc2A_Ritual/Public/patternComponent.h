

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "spellIF.h"
#include "patternComponent.generated.h"

class ApaintActorInterface;
class ABSc2A_RitualCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BSC2A_RITUAL_API UpatternComponent : public UActorComponent, public IspellIF
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UpatternComponent();

	//closeMenu() and handle any spell-doing
	UFUNCTION(BlueprintCallable)
	void endSpellcasting();

	UFUNCTION()
	bool toggleSpell();

	//close paint actor menu and return its current pattern
	UFUNCTION(BlueprintCallable)
	TArray<int32> closeMenu();

	//save player and pass to paint actor
	UFUNCTION(BlueprintCallable)
	void initialize(ABSc2A_RitualCharacter* inPlayer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	ABSc2A_RitualCharacter* player;

	//spellcasting menu
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	ApaintActorInterface* paintActor;

	//FspellPattern spell types and their array of pattern vertex indices
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* spellPatternsTable;
	//spellPatternsTable row names
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> spellIDs;

	UPROPERTY()
	bool inMenu;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};

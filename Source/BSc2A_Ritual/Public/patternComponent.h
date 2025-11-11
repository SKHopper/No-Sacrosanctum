

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

	//open paintActor menu
	UFUNCTION(BlueprintCallable)
	void openMenu();
	//closeMenu() and handle any spell-doing
	UFUNCTION(BlueprintCallable)
	void endSpellcasting();

	//close paint actor menu and return its current pattern
	UFUNCTION(BlueprintCallable)
	TArray<int32> closeMenu();

	//call spell sprite to launch with correct data
	UFUNCTION(BlueprintCallable)
	void doSpell(EspellType spell);

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
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};

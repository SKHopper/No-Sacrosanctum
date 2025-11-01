

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

	UFUNCTION(BlueprintCallable)
	void openMenu();

	UFUNCTION(BlueprintCallable)
	void endMenu();

	UFUNCTION(BlueprintCallable)
	TArray<int32> closeMenu();

	UFUNCTION(BlueprintCallable)
	void doSpell(EspellType spell);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	ABSc2A_RitualCharacter* player;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	ApaintActorInterface* paintActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* spellPatternsTable;

	//UPROPERTY(BlueprintReadOnly)
	//TMap<FString, EspellType> spellPatterns;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};

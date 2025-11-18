

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spellIF.h"
#include "spellable.generated.h"

/*
* 
* Anything able to recieve a spell projectile
* 
*/
UCLASS()
class BSC2A_RITUAL_API Aspellable : 
	public AActor,
	public IspellIF
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aspellable();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EspellType getSpellType(); 

	//call activate() if correct key
	UFUNCTION(BlueprintCallable)
	virtual bool trySpell(EspellType key);

	//override spell toggle functionality
	
	virtual void getSpelled() {};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//set in child constructor
	//TODO:remember if you can set in child header
	EspellType spellType = EspellType::null;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

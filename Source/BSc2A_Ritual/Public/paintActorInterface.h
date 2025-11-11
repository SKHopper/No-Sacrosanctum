// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spellIF.h"
#include "paintActorInterface.generated.h"

class AspellProjectile;

UCLASS()
class BSC2A_RITUAL_API ApaintActorInterface : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ApaintActorInterface();

	//open up menu in blueprint
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void beginPainting();

	//get all spell coord points overlapped this drawing in order
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Data")
	TArray<int32> getPattern();
	//unoverrided
	virtual TArray<int32> getPattern_Implementation();

	//get all spell coord points overlapped this drawing in order
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Data")
	void doSpellSprite(EspellType type);
	//unoverrided
	virtual void doSpellSprite_Implementation(EspellType type);

	//stop painting and return getPattern
	UFUNCTION()
	TArray<int32> endPainting();

	//close this menu
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void stopPainting();

	//init func for bp child
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void initializeBP();

	//spawn our spell projectile (sprite)
	UFUNCTION(BlueprintCallable)
	void initialize(AActor* inPlayer);

	UFUNCTION(BlueprintCallable)
	void setPlayer(AActor* inPlayer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	AActor* player;

	//sprite representation of spell carrying data of effect passed on collision w/objects
	UPROPERTY(BlueprintReadOnly)
	AspellProjectile* spellProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AspellProjectile> BP_spellClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

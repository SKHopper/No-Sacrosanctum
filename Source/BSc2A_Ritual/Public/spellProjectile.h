// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spellProjectile.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class BSC2A_RITUAL_API AspellProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AspellProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* collider;

	UFUNCTION()
	void setPlayer(AActor* inPlayer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 
	UPROPERTY(BlueprintReadOnly)
	AActor* player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

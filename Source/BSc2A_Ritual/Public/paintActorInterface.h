// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spellIF.h"
#include "paintActorInterface.generated.h"

UCLASS()
class BSC2A_RITUAL_API ApaintActorInterface : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ApaintActorInterface();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void beginPainting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Data")
	TArray<int32> getPattern();
	//unoverrided
	virtual TArray<int32> getPattern_Implementation();

	UFUNCTION()
	TArray<int32> endPainting();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void stopPainting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FloodWorldSave.generated.h"

/*
*
* label
*
*/
USTRUCT(BlueprintType)
struct FSave
{
    GENERATED_BODY()

public:

	//
    UPROPERTY(BlueprintReadWrite, Category = "Custom Struct")
    int progression = 0;
};

/**
 * 
 * label
 * 
 */
UCLASS()
class BSC2A_RITUAL_API UFloodWorldSave : public USaveGame
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void set(FSave data);

	UFUNCTION(BlueprintCallable)
	FSave get();

	UFUNCTION(BlueprintCallable)
	void clearSave();

protected:


	UPROPERTY()
	FSave save;

	
};

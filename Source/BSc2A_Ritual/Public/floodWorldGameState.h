// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "floodIF.h"
#include "floodWorldGameState.generated.h"

class AfloodBoard;

/**
 * 
 */
UCLASS()
class BSC2A_RITUAL_API AfloodWorldGameState : public AGameStateBase, public IfloodIF
{
	GENERATED_BODY()

	AfloodWorldGameState();
	
protected:

	//convey self to floodBoards
	virtual void BeginPlay();

	//an un-boarded up body has overflowed
	virtual void bodyFilled();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void gameFailed(bool failByFlood);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AfloodBoard> floodBoardClass;
};

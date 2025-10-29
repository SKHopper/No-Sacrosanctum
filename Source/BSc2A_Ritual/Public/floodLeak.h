// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floodIF.h"
#include "interactionIF.h"
#include "floodLeak.generated.h"

class UBoxComponent;

UCLASS()
/*
 *
 * Interactable leak between two flooded bodies
 * 
 * Manages slow exchange of water between bodies
 * 
 *
 */
class BSC2A_RITUAL_API AfloodLeak : public AActor, public IfloodIF, public IinteractionIF
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfloodLeak();

protected:

	UFUNCTION(BlueprintCallable)
	void endLeak();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double minBeginTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxBeginTime = 120;

	FTimerHandle beginTimer;

	UFUNCTION(BlueprintCallable)
	void queueRandomBegin();

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double minSpawnHeight = 30;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxSpawnHeight = 170;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//remove this leak effect from specified floodBody's
	void stopLeak(int bodyIndex);

	//apply liquid flow from heigher body into lower
	void setOneWay(int bodyIndex, TArray<double>& bodyHeights);

	//time in seconds until bodies will be level
	double predictUnlevelTime(TArray<double>& bodyHeights);

	//leak rate (height per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double leakRate = 1 / 20;

	//height of this leak on the wall
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double leakHeight = 50;

	//is this leak unclosed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canLeak = false;

	//the 2 bodies this leak sits between
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> bodyActors;

	//(INTERFACE CASTED) the 2 bodies this leak sits between
	TArray<IfloodIF*> parentBodies;

	//the current rates of leakage inwards (-rate out, 0, rate in) to each body from this Leak
	TArray<double> bodyLeakRates = { 0, 0 };

	//check bodies' conditions and update flow of liquid accordingly
	UFUNCTION(BlueprintCallable)
	void updateLeak();

	//for use by floodBodies
	virtual void suggestLeakUpdate();

	//call on leak creation, after body initialization
	void beginLeaking();

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double levelizeBodiesThreshold = 1;

	FTimerHandle updateTimer;

	//should not be updated currently
	bool isUpdating = true;
	//
	bool hasUpdatedThisTick = false;
	//
	bool isLeakingAlt = false;
	//
	bool isLeaking = false;

	virtual void interact(bool alternate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floodIF.h"
#include "spellable.h"
//#include "interactionIF.h"
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
class BSC2A_RITUAL_API AfloodLeak : 
	public Aspellable, 
	//public IinteractionIF, 
	public IfloodIF

{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfloodLeak();

protected:

	//stop this leaking, queue next
	UFUNCTION(BlueprintCallable)
	void endLeak();

	//player visible object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;
	//for interact trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* collider;

	//earliest this leak can (re)start
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double minBeginTime = 5;
	//latestest this leak can (re)start
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxBeginTime = 120;

	//for queueing next leak start
	UPROPERTY()
	FTimerHandle beginTimer;
	//set timer to begin leak
	UFUNCTION(BlueprintCallable)
	void queueRandomBegin();

	//randomization guardrail
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double minSpawnHeight = 30;
	//randomization guardrail
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxSpawnHeight = 170;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//remove this leak effect from specified floodBody's
	UFUNCTION()
	void stopLeak(int bodyIndex);

	//apply liquid flow from heigher body into lower
	UFUNCTION()
	void setOneWay(int bodyIndex, TArray<double>& bodyHeights);

	//time in seconds until bodies will be level
	UFUNCTION()
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
	UPROPERTY(BlueprintReadOnly)
	TArray<double> bodyLeakRates = { 0, 0 };

	//check bodies' conditions and update flow of liquid accordingly
	UFUNCTION(BlueprintCallable)
	void updateLeak();

	//for use by floodBodies
	virtual void suggestLeakUpdate();

	//call on leak creation, after body initialization
	void beginLeaking();

	//threshold at which comparitively similar bodies are simply equalized
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double levelizeBodiesThreshold = 1;

	FTimerHandle updateTimer;

	//should not be updated currently
	UPROPERTY()
	bool isUpdating = true;
	//can not update till next time
	UPROPERTY()
	bool hasUpdatedThisTick = false;
	//is leaking from A body into B, should be used to determine the opposite as well
	UPROPERTY()
	bool isLeakingAlt = false;
	//is leaking from any body into the other
	UPROPERTY()
	bool isLeaking = false;

	//stop leak
	virtual void getSpelled();

	//virtual void interact(bool alternate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floodIF.h"
#include "spellable.h"
//#include "interactionIF.h"
#include "floodSource.generated.h"

class UBoxComponent;

UCLASS()
/*
 *
 * Interactable leak from outside to one body
 *
 * Provides constant fast source of liquid height to body
 *
 */
class BSC2A_RITUAL_API AfloodSource : 
	public Aspellable, 
	//public IinteractionIF, 
	public IfloodIF
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfloodSource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//earliest this source can re(start)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double minBeginTime = 5;
	//latestest this source can re(start)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxBeginTime = 40;

	//for queueing next source start
	UPROPERTY()
	FTimerHandle beginTimer;
	//set timer to begin source
	UFUNCTION(BlueprintCallable)
	void queueRandomBegin();

	//player visible object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* collider;
	//for interact trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

	//Are we leaking into our body
	UPROPERTY()
	bool isLeaking = false;

	//leak rate (height per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double leakRate = 0.1;

	//the fluid body this source is leaking into
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* bodyActor;

	//(INTERFACE CASTED) the fluid body this source is leaking into
	IfloodIF* parentBody;

	//leak into body
	UFUNCTION(BlueprintCallable)
	void beginLeak();

	//stop leaking into body
	UFUNCTION(BlueprintCallable)
	void endLeak();

	//stop leak
	virtual void getSpelled();

};

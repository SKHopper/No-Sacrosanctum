// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floodIF.h"
#include "interactionIF.h"
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
class BSC2A_RITUAL_API AfloodSource : public AActor, public IfloodIF, public IinteractionIF
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double minBeginTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxBeginTime = 40;

	UPROPERTY()
	FTimerHandle beginTimer;

	UFUNCTION(BlueprintCallable)
	void queueRandomBegin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

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

	UFUNCTION()
	virtual void interact(bool alternate);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "testCppActor.generated.h"

UCLASS()
class BSC2A_RITUAL_API AtestCppActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AtestCppActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* testMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* testMaterial1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* testMaterial2;

	FTimerHandle timerHandle;

	UFUNCTION(BlueprintCallable)
	void swapMaterial();

};

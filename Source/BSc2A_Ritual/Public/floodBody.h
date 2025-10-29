

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floodIF.h"
#include "floodBody.generated.h"

class UBoxComponent;

UCLASS()
/*
 *
 * Body of liquid that can leak into other bodies or
 * be leaked into from other bodies or a source
 * 
 * Adjusts actor height at most every tick
 * 
 * One per room
 *
 */
class BSC2A_RITUAL_API AfloodBody : public AActor, public IfloodIF
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfloodBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//visible fluid
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* bodyMesh;

	//player overlap
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* bodyCollider;

	//visible fluid material
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* meshMaterial1;

	//amount room has flooded    none->max
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double floodHeight;

	//max height fluid can reach in this body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double maxHeight = 2;

	//current total of all fluid input, height units per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double leakRateTotal;

	//location of this body at BeginPlay
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector startLocation;

	//is flood height zero (0)
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool isBodyDry();

	//how high has this body flooded
	UFUNCTION(BlueprintCallable, BlueprintPure)
	double getHeight();

	//called every tick, changes height by leakRateTotal
	void updateFloodLevel(float DeltaTime);

	//(INTERFACE CASTED) any leaks between this and other bodies
	TArray<IfloodIF*> leaks;
	//
	TMap<double, TArray<IfloodIF*>> heightLeaks;

	//////////floodIF
	
	//adjust leakRateTotal by change
	virtual void changeLeakRate(double change);
	//for use by leaks
	virtual double getBodyHeight();
	//for use by leaks
	virtual double getTotalRate();
	//leaks may call this to register themselves with this
	virtual void conveyLeakActor(AActor* leak, double leakHeight);
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

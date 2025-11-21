

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spellable.h"
#include "floodIF.h"
#include "floodBoard.generated.h"

class UBoxComponent;

UCLASS()
class BSC2A_RITUAL_API AfloodBoard : public Aspellable, public IfloodIF
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfloodBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//make this visually materialize in blueprint
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void boardUpEffect();

	//for spell collison
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* spellCollider;

	//for block collison
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* generalCollider;

	//visible when boarded up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* root;

	//for report overflow
	IfloodIF* gameState;
	virtual void conveyGameState(IfloodIF* gameStateIF);

	//overflow loss condition
	virtual void bodyFilled();

	//become material to board up
	virtual void getSpelled();

	UPROPERTY(BlueprintReadOnly)
	bool notBoardedUp = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

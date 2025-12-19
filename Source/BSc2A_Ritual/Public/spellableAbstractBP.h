

#pragma once

#include "CoreMinimal.h"
#include "spellable.h"
#include "spellableAbstractBP.generated.h"

UCLASS()
class BSC2A_RITUAL_API AspellableAbstractBP : public Aspellable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AspellableAbstractBP();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void onSpelled();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void getSpelled();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

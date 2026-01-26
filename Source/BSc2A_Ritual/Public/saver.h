

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "saver.generated.h"

class UFloodWorldSave;
struct FSave;

UCLASS()
class BSC2A_RITUAL_API Asaver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Asaver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UFloodWorldSave* save;

	UPROPERTY()
	FString slot = "Progress Save Slot";

	UFUNCTION(BlueprintCallable)
	void write(FSave data);

	UFUNCTION(BlueprintCallable)
	FSave read();

	UFUNCTION(BlueprintCallable)
	void clear();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

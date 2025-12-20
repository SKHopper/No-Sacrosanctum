

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "streamBPComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BSC2A_RITUAL_API UstreamBPComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UstreamBPComponent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void start();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void end();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};

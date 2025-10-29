

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "interactionIF.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UinteractionIF : public UInterface
{
	GENERATED_BODY()
};

/*
* 
*/
class BSC2A_RITUAL_API IinteractionIF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//"normal" and "alternate" player interact click
	virtual void interact(bool alternate) {};
	
};

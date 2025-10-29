// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "floodIF.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UfloodIF : public UInterface
{
	GENERATED_BODY()
};

/*
 * 
 * For interaction with floodBodies
 * 
 */
class BSC2A_RITUAL_API IfloodIF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//virtual type identifier() { return default; };

	//recieved by floodBodies
	virtual void changeLeakRate(double change) {};
	//returns from floodBodies
	virtual double getBodyHeight() { return 0; };
	//returns from floodBodies
	virtual double getTotalRate() { return 0; };
	//recieved by floodBodies
	virtual void conveyLeakActor(AActor* leak, double height) {};
	//recieved by floodLeaks
	virtual void suggestLeakUpdate() {};

};

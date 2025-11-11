

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "spellIF.generated.h"

/*
*
* spell applicable uses
*
*/
UENUM(BlueprintType)
enum class EspellType : uint8 
{
    null UMETA(DisplayName = "Null"),
    //stop floodSource leak
	source UMETA(DisplayName = "Source"),
    //stop leakSource leak
	leak UMETA(DisplayName = "Leak"),
    //board up flooding room
	boardUp UMETA(DisplayName = "Board Up")
    //

    //

    //

    //

    //
};


/*
*
* one spell per pattern, one pattern per spell
* 
*/
USTRUCT(BlueprintType)
struct FspellPattern : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Struct")
    EspellType spellType;

    //ascending order pattern overlapped grid points' indicies
    //note this is a string of integers as patterns are often listed and TArray UPROPERTYs can not contain TArrays
    //and we are avoiding dynamically producing C array int*
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Struct")
    FString pattern;

    FspellPattern(
        EspellType inType = EspellType::null,
        FString inPattern = FString()
    )
        : spellType(inType), pattern(inPattern)
    {}
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UspellIF : public UInterface
{
	GENERATED_BODY()
};

/*
*
* For interaction between spell objects and spellable objects
*
 */
class BSC2A_RITUAL_API IspellIF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
};



#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "spellIF.generated.h"

UENUM(BlueprintType)
enum class EspellType : uint8 {
    null UMETA(DisplayName = "Null"),
	source UMETA(DisplayName = "Source"),
	leak UMETA(DisplayName = "Leak"),
	boardUp UMETA(DisplayName = "Board Up")
};

USTRUCT(BlueprintType)
struct FspellPattern
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Struct")
    EspellType spellType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Struct")
    TArray<int32> pattern;

    //default constructor
    FspellPattern(
        EspellType inType = EspellType::null,
        TArray<int32> inPattern = TArray<int32>()
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

/**
 * 
 */
class BSC2A_RITUAL_API IspellIF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
};

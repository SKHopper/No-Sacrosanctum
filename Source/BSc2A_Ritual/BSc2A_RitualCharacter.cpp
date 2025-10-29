// Copyright Epic Games, Inc. All Rights Reserved.

#include "BSc2A_RitualCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "patternComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BSc2A_Ritual.h"

ABSc2A_RitualCharacter::ABSc2A_RitualCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	//
	patternComp = CreateDefaultSubobject<UpatternComponent>(TEXT("Pattern Logic Component"));
}

// Called when the game starts or when spawned
void ABSc2A_RitualCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABSc2A_RitualCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABSc2A_RitualCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABSc2A_RitualCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABSc2A_RitualCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABSc2A_RitualCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ABSc2A_RitualCharacter::LookInput);

		//
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Completed, this, &ABSc2A_RitualCharacter::doInteract);
		//
		EnhancedInputComponent->BindAction(altInteractAction, ETriggerEvent::Completed, this, &ABSc2A_RitualCharacter::doAltInteract);

		EnhancedInputComponent->BindAction(spellMenuAction, ETriggerEvent::Completed, this, &ABSc2A_RitualCharacter::toggleSpellMenu);
	}
	else
	{
		UE_LOG(LogBSc2A_Ritual, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABSc2A_RitualCharacter::toggleSpellMenu() {
	if (inSpellMenu) {
		inSpellMenu = false;
		patternComp->closeMenu();
	}
	else {
		inSpellMenu = true;
		patternComp->openMenu();
	}
}


void ABSc2A_RitualCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ABSc2A_RitualCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ABSc2A_RitualCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ABSc2A_RitualCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ABSc2A_RitualCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ABSc2A_RitualCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ABSc2A_RitualCharacter::doInteract() {
	tryInteract(false);
}

void ABSc2A_RitualCharacter::doAltInteract() {
	tryInteract(true);
}

void ABSc2A_RitualCharacter::tryInteract(bool isAlt) {
	FCollisionQueryParams traceParams = FCollisionQueryParams(
		FName(TEXT("RV_Trace")),
		true,
		this
	);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;

	FHitResult traceHit;

	if (
		GetWorld()->LineTraceSingleByChannel(
			traceHit,
			GetFirstPersonCameraComponent()->GetComponentLocation(),
			GetFirstPersonCameraComponent()->GetComponentLocation() + GetFirstPersonCameraComponent()->GetForwardVector() * interactTraceLength,
			ECC_Visibility,
			traceParams
		)
	) {
		AActor* hitActor = traceHit.GetActor();
		if (hitActor) {
			if (hitActor->GetClass()->ImplementsInterface(UinteractionIF::StaticClass())) {
				Cast<IinteractionIF>(hitActor)->interact(isAlt);
			}
		}
	}
}
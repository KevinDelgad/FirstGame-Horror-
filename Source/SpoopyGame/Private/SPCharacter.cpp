// Fill out your copyright notice in the Description page of Project Settings.


#include "SPCharacter.h"

#include "SPInteractComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASPCharacter::ASPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeadConnectionName = FName("head");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(GetMesh());
	CameraComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	InteractComp = CreateDefaultSubobject<USPInteractComponent>("InteractComponent");
	
}

// Called when the game starts or when spawned
void ASPCharacter::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules ATR = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	CameraComp->AttachToComponent(GetMesh(), ATR, HeadConnectionName);
}

// Called every frame
void ASPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASPCharacter::MoveForward(float Value)
{
	FRotator ControllerRotator = GetController()->GetControlRotation();

	//Ensures Only Yaw Direction is taken into account when adding movement Input
	ControllerRotator.Pitch = 0.0f;
	ControllerRotator.Roll = 0.0f;

	// Move in Direction Controller Looks * Value (Forward/Backwards)
	AddMovementInput(ControllerRotator.Vector(), Value);
}

void ASPCharacter::MoveRight(float Value)
{
	FRotator ControllerRotator = GetController()->GetControlRotation();

	//Ensures Only Yaw Direction is taken into account when adding movement Input 
	ControllerRotator.Pitch = 0.0f;
	ControllerRotator.Roll = 0.0f;

	//Get Y (Right) Axis of Controller Rotation Matrix
	FVector RightVector = FRotationMatrix(ControllerRotator).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ASPCharacter::PerformInteract()
{
	if (InteractComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractComp->IsInteracting"));
		InteractComp->Interact();
	}
}

// Called to bind functionality to input
void ASPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ASPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPCharacter::MoveRight);

	//Camera Control
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	//Interact
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASPCharacter::PerformInteract);
}


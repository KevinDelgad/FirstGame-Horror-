// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPCharacter.generated.h"

class USPActionComponent;
class USPInteractComponent;
class UCameraComponent;

UCLASS()
class SPOOPYGAME_API ASPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void PerformInteract();

	void Pickup();
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USPInteractComponent* InteractComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USPActionComponent* ActionComp;

	FName HeadConnectionName;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

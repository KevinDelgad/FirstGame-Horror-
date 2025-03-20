// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPAction.h"
#include "SPAction_Pickup.generated.h"

class ASPCharacter;
/**
 * 
 */
UCLASS()
class SPOOPYGAME_API USPAction_Pickup : public USPAction
{
	GENERATED_BODY()

	protected:

	UPROPERTY(BlueprintReadOnly)
	AActor* HitTarget;

	//Raycast for objectToPickup
	bool SetHitTarget(const ASPCharacter* InstigatorCharacter);

	UPROPERTY(EditDefaultsOnly)
	float ReachDistance;

	UPROPERTY(EditDefaultsOnly)
	float TraceRadius;
	
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> HitChannel;
	public:
	
	virtual void StartAction_Implementation(AActor* Instigator) override;

	//virtual void EndAction_Implementation() override;

public:
	USPAction_Pickup();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPAction.h"
#include "SPAction_Pickup.generated.h"

class ASPPickupBase;
class ASPCharacter;
/**
 * 
 */
UCLASS()
class SPOOPYGAME_API USPAction_Pickup : public USPAction , public FTickableGameObject
{
	GENERATED_BODY()

	private:
	// The last frame number we were ticked.
	// We don't want to tick multiple times per frame 
	uint32 LastFrameNumberWeTicked = INDEX_NONE;
	
	protected:

	UFUNCTION(BlueprintCallable, Category = "PickUp")
	AActor* CreateActorClone( AActor* Instigator ,TSubclassOf<AActor> PickUpObj, FTransform PickupTransform);

	UPROPERTY(BlueprintReadOnly)
	AActor* HitTarget;

	//Raycast for objectToPickup
	bool SetHitTarget(const ASPCharacter* InstigatorCharacter);

	UPROPERTY(EditDefaultsOnly)
	float ReachDistance;

	UPROPERTY(EditDefaultsOnly)
	float TraceRadius;

	UPROPERTY(BlueprintReadWrite)
	bool bHolding = false;
	
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> HitChannel;
	public:
	
	virtual void StartAction_Implementation(AActor* Instigator) override;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	FHitResult GetHitResult(const ASPCharacter* InstigatorCharacter);
	
	
	//virtual void EndAction_Implementation() override;
	
public:
	USPAction_Pickup();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual void Tick(float DeltaTime) override;
	
	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Conditional;
	}
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MyTickableClass, STATGROUP_Tickables);
	}
	virtual bool IsTickable() const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void BPTick(float DeltaTime);
};

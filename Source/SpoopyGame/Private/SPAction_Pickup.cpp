// Fill out your copyright notice in the Description page of Project Settings.


#include "SPAction_Pickup.h"

#include "SPCharacter.h"
#include "SPPickupBase.h"
#include "Camera/CameraComponent.h"

USPAction_Pickup::USPAction_Pickup()
{
	ReachDistance = 100.0f;
	TraceRadius = 20.0f;
}

void USPAction_Pickup::Tick(float DeltaTime)
{
	if (LastFrameNumberWeTicked == GFrameCounter)
		return;


	BPTick(DeltaTime);
	
	LastFrameNumberWeTicked = GFrameCounter;
}

bool USPAction_Pickup::IsTickable() const
{
	return bHolding;
}

AActor* USPAction_Pickup::CreateActorClone(AActor* Instigator, TSubclassOf<AActor> PickUpObj, FTransform PickupTransform)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Cast<APawn>(Instigator);
	
	return GetWorld()->SpawnActor<AActor>(PickUpObj, PickupTransform, SpawnParams);
}

FHitResult USPAction_Pickup::GetHitResult(const ASPCharacter* InstigatorCharacter)
{
	FHitResult HitResult;

	FVector EyeLocation = InstigatorCharacter->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
	FRotator EyeRotation = InstigatorCharacter->GetControlRotation();

	FVector End = EyeLocation + (EyeRotation.Vector() * ReachDistance);

	FName ProfileToBlock = "BlockAllStatic";
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByProfile(HitResult, EyeLocation, End, ProfileToBlock);
	
	return HitResult;
}

bool USPAction_Pickup::SetHitTarget(const ASPCharacter* InstigatorCharacter)
{
	
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(HitChannel);

	FVector EyeLocation = InstigatorCharacter->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
	FRotator EyeRotation = InstigatorCharacter->GetControlRotation();

	FVector End = EyeLocation + (EyeRotation.Vector() * ReachDistance);

	FHitResult Hit;

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, EyeLocation, End, FQuat::Identity,
		params, Shape);
	
	if (bBlockingHit)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			HitTarget = HitActor;
			return true;
		}
	}
	
	return false;
}

void USPAction_Pickup::StartAction_Implementation(AActor* Instigator)
{
	ASPCharacter* Character = Cast<ASPCharacter>(Instigator);

	if (Character)
	{
		if (!SetHitTarget(Character))
		{
			return;
		}
	}

	Super::StartAction_Implementation(Instigator);
}



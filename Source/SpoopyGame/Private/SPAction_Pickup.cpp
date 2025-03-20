// Fill out your copyright notice in the Description page of Project Settings.


#include "SPAction_Pickup.h"

#include "SPCharacter.h"
#include "Camera/CameraComponent.h"

USPAction_Pickup::USPAction_Pickup()
{
	ReachDistance = 100.0f;
	TraceRadius = 20.0f;
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
		if (SetHitTarget(Character))
		{
			return;
		}
	}

	Super::StartAction_Implementation(Instigator);
}



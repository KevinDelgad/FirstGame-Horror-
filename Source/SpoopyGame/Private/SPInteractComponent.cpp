// Fill out your copyright notice in the Description page of Project Settings.


#include "SPInteractComponent.h"

#include "SPInteractInterface.h"

// Sets default values for this component's properties
USPInteractComponent::USPInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InteractDistance = 160.0f;
	TraceRadius = 10.0f;
	CollisionChannel = ECC_WorldStatic;
}


// Called when the game starts
void USPInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USPInteractComponent::Interact()
{
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(CollisionChannel);

	APawn* PawnOwner = Cast<APawn>(GetOwner());

	FVector EyeLocation;
	FRotator EyeRotation;
	
	PawnOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * InteractDistance);

	FHitResult Hit;

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, EyeLocation, End, FQuat::Identity,
		params, Shape);
	
	if (bBlockingHit)
	{
		
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<USPInteractInterface>())
			{
				ISPInteractInterface::Execute_Interact(HitActor);
			}
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, FColor::White, false, 5, 0, 2.0f);
}


// Called every frame
void USPInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


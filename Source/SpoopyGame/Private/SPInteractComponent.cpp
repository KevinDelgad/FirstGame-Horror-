// Fill out your copyright notice in the Description page of Project Settings.


#include "SPInteractComponent.h"

#include "SPCharacter.h"
#include "SPInteractInterface.h"
#include "SWorldUserWidget.h"
#include "Camera/CameraComponent.h"

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


// Called every frame
void USPInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	TargetActor = nullptr;
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(CollisionChannel);

	ASPCharacter* PawnOwner = Cast<ASPCharacter>(GetOwner());

	FVector EyeLocation = PawnOwner->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
	FRotator EyeRotation = PawnOwner->GetControlRotation();

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
				TargetActor = HitActor;
			}

			if (TargetActor)
			{
				if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
				{
					DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(), DefaultWidgetClass);
				}

				if (DefaultWidgetInstance)
				{
					DefaultWidgetInstance->AttachedActor = TargetActor;

					
					
					if (!DefaultWidgetInstance->IsInViewport())
					{
						DefaultWidgetInstance->AddToViewport();
					}
				}
			}
			else
			{
				if (DefaultWidgetInstance)
				{
					DefaultWidgetInstance->RemoveFromParent();
				}
			}
		}
	}
	//DrawDebugLine(GetWorld(), EyeLocation, End, FColor::White, false, 30, 0, 2.0f);
}

void USPInteractComponent::Interact()
{
	if (TargetActor != nullptr)
	{
		ISPInteractInterface::Execute_Interact(TargetActor, Cast<APawn>(GetOwner()));
	}
}

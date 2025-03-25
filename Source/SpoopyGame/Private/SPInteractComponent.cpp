// Fill out your copyright notice in the Description page of Project Settings.


#include "SPInteractComponent.h"

#include "SPCharacter.h"
#include "SPGameplayFunctionLibrary.h"
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
	HighlightActor = nullptr;
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FCollisionObjectQueryParams params;

	if (ensure(!ChannelsToCollide.IsEmpty()))
	{
		for (TEnumAsByte Channel : ChannelsToCollide)
		{
			params.AddObjectTypesToQuery(Channel);
		}
	}

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
			//Interaction Check
			if (HitActor->Implements<USPInteractInterface>())
			{
				TargetActor = HitActor;
			}

			// Pickup / Highlight Check
			if (ensure(PickupActorClass) && HitActor->IsA(PickupActorClass))
			{
				HighlightActor = HitActor;
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


			if (HighlightActor)
			{
				//Current Iteration Found Mesh
				UStaticMeshComponent* FoundHighlightMesh = HighlightActor->FindComponentByClass<UStaticMeshComponent>();

				//Check for previously found Mesh and clear if not current found mesh
				if (HighlightedActorMesh && HighlightedActorMesh != FoundHighlightMesh)
				{
					HighlightedActorMesh->SetOverlayMaterial(nullptr);
				}

				//Set New Highlight if No Highlight found or New Highlight object is selected
				if ( !HighlightedActorMesh || (HighlightedActorMesh != FoundHighlightMesh))
				{
					//Set Highlight on Actor
					HighlightedActorMesh = FoundHighlightMesh;
					if (HighlightedActorMesh)
					{
						HighlightedActorMesh->SetOverlayMaterial(HighlightMaterial);
					}
				}
			}
			else
			{
				if (HighlightedActorMesh)
				{
					//Clear current Highlight and clear reference (If Found)
					HighlightedActorMesh->SetOverlayMaterial(nullptr);
					HighlightedActorMesh = nullptr;
				}
			}

		}
	}
	//DrawDebugLine(GetWorld(), EyeLocation, End, FColor::White, false, 30, 0, 2.0f);
}

void USPInteractComponent::Interact()
{

	if (ensureMsgf(InteractTag.IsValid(), TEXT("Interact Tag Not Set")))
	{
		if (TargetActor != nullptr && !USPGameplayFunctionLibrary::CheckPlayerForTag(GetOwner(), InteractTag))
		{
			ISPInteractInterface::Execute_Interact(TargetActor, Cast<APawn>(GetOwner()));
		}
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "SPActionComponent.h"

#include "SPAction.h"

// Sets default values for this component's properties
USPActionComponent::USPActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USPActionComponent::BeginPlay()
{
	Super::BeginPlay();

	//Add All Default Actions
	for (TSubclassOf ActionClass: DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
	
}


// Called every frame
void USPActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USPActionComponent::AddAction(AActor* Instigator, TSubclassOf<USPAction> ActionClass)
{

	if (!ensure(ActionClass))
	{
		return false;
	}
	
	USPAction* NewAction = NewObject<USPAction>(GetOuter(), ActionClass);
	
	if (CheckForAction(NewAction->ActionName))
	{
		return false;
	}

	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
		NewAction->Initialize(this);
		return true;
	}


	return false;
}

bool USPActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (USPAction* Action : Actions)
	{
		UE_LOG(LogTemp, Warning, TEXT("Action: %s"), *ActionName.ToString());
		UE_LOG(LogTemp, Warning, TEXT("FocusedAction: %s"), *Action->ActionName.ToString());
		
		//Find Action By Name
		if (Action->ActionName == ActionName)
		{
			//Check if Action Can run
			if (Action->CanStart())
			{
				Action->StartAction(Instigator);
				return true;
			}
		}
	}
	
	return false;
}

bool USPActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (USPAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->EndAction(Instigator);
				return true;
			}
		}
	}

	return false;
}

bool USPActionComponent::CheckForAction(FName ActionName)
{

	for (USPAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			return true;
		}
	}
	
	return false;
}


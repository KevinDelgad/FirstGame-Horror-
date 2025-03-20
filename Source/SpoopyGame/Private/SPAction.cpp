// Fill out your copyright notice in the Description page of Project Settings.


#include "SPAction.h"

#include "SPActionComponent.h"

void USPAction::StartAction_Implementation(AActor* Instigator)
{
	//Make Sure To Always add Gameplay Tags
	ActionComponent->ActiveGameplayTags.AppendTags(GrantsTags);
}

void USPAction::EndAction_Implementation(AActor* Instigator)
{
	//Make Sure to Always Clear Previously added Tags
	ActionComponent->ActiveGameplayTags.RemoveTags(GrantsTags);
}


//Check for previously started Action / Blocking Tags
bool USPAction::CanStart_Implementation()
{
	if (IsRunning())
	{
		return false;
	}

	USPActionComponent* ActionComp = GetOwningComponent();

	if (ActionComp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

USPActionComponent* USPAction::GetOwningComponent() const
{
	return ActionComponent;
}

UWorld* USPAction::GetGameWorld()
{
	return GetWorld();
}

void USPAction::Initialize(USPActionComponent* NewActionComp)
{
	ActionComponent = NewActionComp;
}

bool USPAction::IsRunning() const
{
	return bIsRunning;
}

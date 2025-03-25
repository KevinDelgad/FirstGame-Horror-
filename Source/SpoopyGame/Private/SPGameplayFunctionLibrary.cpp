// Fill out your copyright notice in the Description page of Project Settings.


#include "SPGameplayFunctionLibrary.h"

#include "SPActionComponent.h"

bool USPGameplayFunctionLibrary::CheckPlayerForTag(AActor* TargetActor, FGameplayTag TagToCheck)
{
	USPActionComponent* ActionComponent = USPActionComponent::GetActions(TargetActor);

	if (ensureMsgf(TagToCheck.IsValid(), TEXT("GameplayTagToCheck is invalid!")))
	{
		if (ActionComponent)
		{
			FGameplayTagContainer ActiveGameplayTags = ActionComponent->ActiveGameplayTags;
			return ActiveGameplayTags.HasTag(TagToCheck);
		}
	}
	
	return false;
}

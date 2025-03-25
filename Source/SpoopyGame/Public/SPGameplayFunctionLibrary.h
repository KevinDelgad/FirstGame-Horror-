// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SPGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPOOPYGAME_API USPGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool CheckPlayerForTag(AActor* TargetActor, FGameplayTag TagToCheck);
};

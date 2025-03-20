// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SPAction.generated.h"

class USPActionComponent;
/**
 * 
 */

UCLASS(Blueprintable)
class SPOOPYGAME_API USPAction : public UObject
{
	GENERATED_BODY()

	protected:

	UFUNCTION(BlueprintCallable, Category="Action")
	USPActionComponent* GetOwningComponent() const;

	
	UFUNCTION(BlueprintCallable, Category="Action")
	UWorld* GetGameWorld();
	
	bool bIsRunning;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY()
	USPActionComponent* ActionComponent;
	
	public:

	void Initialize(USPActionComponent* NewActionComp);
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FName ActionName;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void EndAction(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart();

	bool IsRunning() const;

};

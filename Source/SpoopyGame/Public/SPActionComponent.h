// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SPActionComponent.generated.h"


class USPAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOPYGAME_API USPActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//When Dealing with pointers and Memory, Mark with UPROPERTY to tell unreal there is memory here to keep track of
	UPROPERTY()
	TArray<USPAction*> Actions;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TArray<TSubclassOf<USPAction>> DefaultActions;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	FGameplayTagContainer ActiveGameplayTags;
	
	UFUNCTION(BlueprintCallable, Category="Action")
	bool AddAction(AActor* Instigator, TSubclassOf<USPAction> ActionClass);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator ,FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator ,FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool CheckForAction(FName ActionName);
};

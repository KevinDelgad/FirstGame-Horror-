// Fill out your copyright notice in the Description page of Project Settings.


#include "SPBoxTrigger.h"

#include "Components/BoxComponent.h"

// Sets default values
ASPBoxTrigger::ASPBoxTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
}

void ASPBoxTrigger::TriggerFire_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Implement in Children Functiion
}


void ASPBoxTrigger::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


void ASPBoxTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASPBoxTrigger::OnActorOverlap);
}



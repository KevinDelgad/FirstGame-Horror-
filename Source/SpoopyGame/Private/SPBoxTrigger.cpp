// Fill out your copyright notice in the Description page of Project Settings.


#include "SPBoxTrigger.h"

#include "Components/BoxComponent.h"

// Sets default values
ASPBoxTrigger::ASPBoxTrigger()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(Root);
}

void ASPBoxTrigger::TriggerFire_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Implement in Children Function
}


void ASPBoxTrigger::EndTriggerFire_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Implement in Children Function
}

void ASPBoxTrigger::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TriggerFire(OverlappedComponent,OtherActor,OtherComp, OtherBodyIndex,bFromSweep, SweepResult);
}

void ASPBoxTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EndTriggerFire(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


void ASPBoxTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASPBoxTrigger::OnActorOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASPBoxTrigger::OnOverlapEnd);
}



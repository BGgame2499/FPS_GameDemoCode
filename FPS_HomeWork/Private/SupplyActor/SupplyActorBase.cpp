// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplyActor/SupplyActorBase.h"

#include "Components/BoxComponent.h"

ASupplyActorBase::ASupplyActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	
	OverlapBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
	OverlapBoxComponent->SetupAttachment(MeshComponent);
	
	OverlapBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASupplyActorBase::BoxBeginOverlap);
}

void ASupplyActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASupplyActorBase::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	BoxBeginOverlapActor(OtherActor);
}

void ASupplyActorBase::BoxBeginOverlapActor(AActor* OverlappingActor)
{
}

void ASupplyActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


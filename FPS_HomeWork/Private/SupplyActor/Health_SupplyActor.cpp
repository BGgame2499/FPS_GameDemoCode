// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplyActor/Health_SupplyActor.h"

#include "Components/HealthComponent.h"
#include "FPS_HomeWork/FPS_HomeWorkCharacter.h"

AHealth_SupplyActor::AHealth_SupplyActor()
{
	SupplyHealthAmount = 20.f;
}

void AHealth_SupplyActor::BeginPlay()
{
	Super::BeginPlay();
}

void AHealth_SupplyActor::BoxBeginOverlapActor(AActor* OverlappingActor)
{
	Super::BoxBeginOverlapActor(OverlappingActor);
	
	AFPS_HomeWorkCharacter* Character = Cast<AFPS_HomeWorkCharacter>(OverlappingActor);
	if (Character)
	{
		UHealthComponent* HealthComponent = Cast<UHealthComponent>(Character->GetDefaultSubobjectByName(TEXT("HealthComponent")));
		if (HealthComponent)
		{
			if (HealthComponent->Heal(SupplyHealthAmount))
			{
				UE_LOG(LogTemp, Log, TEXT("HealthSupplyDestroy!"));
				Destroy();
				return;
			}
			
			UE_LOG(LogTemp, Log, TEXT("Can not add Health!"));
		}
	}
}

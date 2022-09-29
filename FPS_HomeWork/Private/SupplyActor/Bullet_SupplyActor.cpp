// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplyActor/Bullet_SupplyActor.h"

#include "FPS_HomeWork/FPS_HomeWorkCharacter.h"

ABullet_SupplyActor::ABullet_SupplyActor()
{
	SupplyBulletAmount = 60;
}

void ABullet_SupplyActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet_SupplyActor::BoxBeginOverlapActor(AActor* OverlappingActor)
{
	Super::BoxBeginOverlapActor(OverlappingActor);
	
	AFPS_HomeWorkCharacter* Character = Cast<AFPS_HomeWorkCharacter>(OverlappingActor);
	if (Character)
	{
		UBulletComponent* BulletComponent = Cast<UBulletComponent>(Character->GetDefaultSubobjectByName(TEXT("BulletComponent")));
		if (BulletComponent)
		{
			BulletComponent->AddBullet(SupplyBulletAmount);
			UE_LOG(LogTemp, Log, TEXT("BulletSupplyDestroy!"));
			Destroy();
			return;
		}
	}
}

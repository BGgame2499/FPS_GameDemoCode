// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SupplyActor/SupplyActorBase.h"
#include "Bullet_SupplyActor.generated.h"

/**
 * 
 */
UCLASS()
class FPS_HOMEWORK_API ABullet_SupplyActor : public ASupplyActorBase
{
	GENERATED_BODY()
	
public:

	ABullet_SupplyActor();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SupplyBulletAmount;
	
	virtual void BeginPlay() override;
protected:
	virtual void BoxBeginOverlapActor(AActor* OverlappingActor) override;
};

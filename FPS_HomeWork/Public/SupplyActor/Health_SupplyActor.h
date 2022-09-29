// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SupplyActor/SupplyActorBase.h"
#include "Health_SupplyActor.generated.h"

/**
 * 
 */
UCLASS()
class FPS_HOMEWORK_API AHealth_SupplyActor : public ASupplyActorBase
{
	GENERATED_BODY()
public:
	AHealth_SupplyActor();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SupplyHealthAmount;
	
	virtual void BeginPlay() override;
protected:
	virtual void BoxBeginOverlapActor(AActor* OverlappingActor) override;
};

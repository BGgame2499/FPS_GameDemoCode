// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_HOMEWORK_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};

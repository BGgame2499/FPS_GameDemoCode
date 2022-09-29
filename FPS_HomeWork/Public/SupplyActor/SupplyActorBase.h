// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SupplyActorBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FPS_HOMEWORK_API ASupplyActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASupplyActorBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Components)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Components)
	UBoxComponent* OverlapBoxComponent;
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void BoxBeginOverlapActor(AActor* OverlappingActor);
public:	
	virtual void Tick(float DeltaTime) override;

};

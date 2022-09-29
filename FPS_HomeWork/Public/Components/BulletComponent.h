// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_HOMEWORK_API UBulletComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBulletComponent();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletComponent")
	int32 DefaultCarryBullets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletComponent")
	int32 DefaultClipBullets;
	
	int32 CarryBullets;
	int32 ClipBullets;

	
	UPROPERTY(BlueprintReadOnly, Category = "BulletComponent")
	bool bIsReloading;
	
	UPROPERTY(BlueprintReadOnly, Category = "BulletComponent")
	float ReloadingTime;

	FTimerHandle ReloadTimerHandle;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Fire();
	bool Reload();

	bool AddBullet(int32 BulletAmount);
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentClipBullets();
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentCarryBullets();
private:
	
	UFUNCTION()
	void ReloadEnd();


};

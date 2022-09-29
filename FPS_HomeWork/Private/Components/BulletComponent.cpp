// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BulletComponent.h"

UBulletComponent::UBulletComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	
	DefaultCarryBullets = 240;
	DefaultClipBullets = 30;
	
	ReloadingTime = 2.f;
	bIsReloading = false;
}


void UBulletComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CarryBullets = DefaultCarryBullets;
	ClipBullets = DefaultClipBullets;

}


void UBulletComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UBulletComponent::Fire()
{
	if (!bIsReloading)
	{
		if (GetCurrentClipBullets() <= 0)
		{
			Reload();
			return false;
		}

		ClipBullets--;
		return true;
	}
	return false;
}

bool UBulletComponent::Reload()
{
	if (GetCurrentClipBullets() >= DefaultClipBullets || bIsReloading)
	{
		return false;
	}

	//
	//
	if (GetCurrentCarryBullets() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle ,this, &UBulletComponent::ReloadEnd,ReloadingTime,false);
		
		bIsReloading = true;
		
		return true;
	}
	else
	{
		return false;
	}
	
	return false;
}

void UBulletComponent::ReloadEnd()
{
	const int32 NeedBulletNum = DefaultClipBullets - ClipBullets;
	if (GetCurrentCarryBullets() >= NeedBulletNum)
	{
		ClipBullets += NeedBulletNum;
		CarryBullets -= NeedBulletNum;
	}
	else
	{
		ClipBullets += GetCurrentCarryBullets();
		CarryBullets = 0;
	}
	
	bIsReloading = false;
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
}

bool UBulletComponent::AddBullet(int32 BulletAmount)
{
	if (BulletAmount > 0)
	{
		CarryBullets += BulletAmount;
		return true;
	}
	return false;
}

int32 UBulletComponent::GetCurrentClipBullets()
{
	return ClipBullets;
}

int32 UBulletComponent::GetCurrentCarryBullets()
{
	return CarryBullets;
}


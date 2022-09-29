// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "FPS_HomeWork/FPS_HomeWorkGameMode.h"

UHealthComponent::UHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.0f;

	bIsDead = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor * MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);	//Bind the Actor for TakeAnyDamage event
	}
	
	Health = DefaultHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::HandleTakeAnyDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	bIsDead = Health <= 0.0f;

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);	//广播事件

	UE_LOG(LogTemp, Log, TEXT("Health Changed : %s"), *FString::SanitizeFloat(Health));

	if (bIsDead)	//如果当前角色已死亡则向GameMode广播消息
	{
		AFPS_HomeWorkGameMode * GameMode = Cast<AFPS_HomeWorkGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnActorKilled.Broadcast(GetOwner(), DamageCauser, InstigatedBy);
		}
	}
	
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

bool UHealthComponent::Heal(float HealthAmount)
{
	if (HealthAmount <= 0 || Health <= 0 || Health >= DefaultHealth)
	{
		return false;
	}

	Health = FMath::Clamp(Health + HealthAmount, 0.0f, DefaultHealth);

	OnHealthChanged.Broadcast(this, Health, -HealthAmount, nullptr, nullptr, nullptr);

	return true;
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_HomeWorkGameMode.h"
#include "FPS_HomeWorkHUD.h"
#include "FPS_HomeWorkCharacter.h"
#include "SpawnEnemyActor.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_HomeWorkGameMode::AFPS_HomeWorkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	PrimaryActorTick.bCanEverTick = true;
	
	// use our custom HUD class
	HUDClass = AFPS_HomeWorkHUD::StaticClass();

	FPSGameState = GameStateEnum::Playing;
	
	TargetScore = 50;
	Score = 0;
	bIsAllEnemiesDead = false;
	
	OnActorKilled.AddDynamic(this,&ThisClass::ActorKilled);
}

void AFPS_HomeWorkGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(GenerateEnemyTimeHandle ,this, &ThisClass::GenerateEnemy,0.5,true,0.0f);
}

void AFPS_HomeWorkGameMode::ActorKilled(AActor* VictimActor, AActor* KillerActor, AController* KillerController)
{
	AFPS_HomeWorkCharacter* Character = Cast<AFPS_HomeWorkCharacter>(VictimActor);
	if (Character)
	{
		FPSGameState = GameStateEnum::Failed;
		Character->DetachFromControllerPendingDestroy();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		UE_LOG(LogTemp, Log, TEXT("Player be killed!"));
		GenerateEnemyEnd();
	}
	
	ATP_ThirdPersonCharacter* TPCharacter = Cast<ATP_ThirdPersonCharacter>(VictimActor);
	if (TPCharacter)
	{
		Score += TPCharacter->ScoreValue;
		if (Score >= TargetScore)
		{
			FPSGameState = GameStateEnum::Win;
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
			UE_LOG(LogTemp, Log, TEXT("Player Win!"));
			GenerateEnemyEnd();
		}
	}
}

void AFPS_HomeWorkGameMode::GenerateEnemy()
{
	if (bIsAllEnemiesDead)
	{
		if (EnemyWaves[CurrentEnemyWave] > 0)
		{
			TArray<AActor*> FoundActorLocations;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnEnemyActor::StaticClass(), FoundActorLocations);	//获取全部生成位置
			if (FoundActorLocations.Num() > 0)
			{
				
				AActor* ActorLocation = FoundActorLocations[FMath::RandRange(0, FoundActorLocations.Num() - 1)];
				FVector Vec = ActorLocation->GetActorLocation();
				FRotator Rot = ActorLocation->GetActorRotation();
				FActorSpawnParameters SpawnParameters;
				if(GetWorld()->SpawnActor(GenerateEnemyType,&Vec,&Rot,SpawnParameters))
				{
					EnemyWaves[CurrentEnemyWave]--;
				}
			}
		}
		else if (CurrentEnemyWave < EnemyWaves.Num())
		{
			CurrentEnemyWave++;
			
			if (CurrentEnemyWave >= EnemyWaves.Num())	//如果已经是最后一波敌人则停止生成逻辑
			{
				GenerateEnemyEnd();
			}
		}
	}
}

void AFPS_HomeWorkGameMode::GenerateEnemyEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(GenerateEnemyTimeHandle);
	PrimaryActorTick.bCanEverTick = false;
	
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATP_ThirdPersonCharacter::StaticClass(), FoundEnemies);
	for (int32 Index = 0; Index < FoundEnemies.Num();Index++)
	{
		ATP_ThirdPersonCharacter* Enemy = Cast<ATP_ThirdPersonCharacter>(FoundEnemies[Index]);
		if (Enemy)
		{
			Enemy->GetMovementComponent()->SetActive(false);
			
		}
	}
	
}

void AFPS_HomeWorkGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATP_ThirdPersonCharacter::StaticClass(), FoundEnemies);
	if (FoundEnemies.Num() <= 0)
	{
		bIsAllEnemiesDead = true;
	}
	else if(EnemyWaves[CurrentEnemyWave] <= 0)
	{
		bIsAllEnemiesDead = false;
	}
}


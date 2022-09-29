// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_HomeWorkGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor,AController*,KillerController);

UENUM(Blueprintable, BlueprintType)
enum class GameStateEnum : uint8
{
	Playing,
	Win,
	Failed
};

class ATP_ThirdPersonCharacter;

UCLASS(minimalapi)
class AFPS_HomeWorkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS_HomeWorkGameMode();

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "GameMode")
	TSubclassOf<ATP_ThirdPersonCharacter> GenerateEnemyType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "GameMode")
	TArray<int32> EnemyWaves; 
	
	UPROPERTY(BlueprintReadOnly,Category = "GameMode")
	bool bIsAllEnemiesDead;
	
	UPROPERTY(BlueprintReadWrite)
	GameStateEnum FPSGameState;
	
	UPROPERTY(BlueprintAssignable,Category = "GameMode")
	FOnActorKilled OnActorKilled;

	UPROPERTY(BlueprintReadOnly)
	int32 Score;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Score")
	int32 TargetScore;
private:
	int32 CurrentEnemyWave;
protected:
	UFUNCTION()
	void ActorKilled(AActor* VictimActor, AActor* KillerActor,AController* KillerController);

	FTimerHandle GenerateEnemyTimeHandle;

	UFUNCTION()
	void GenerateEnemy();

	UFUNCTION(BlueprintCallable)
	void GenerateEnemyEnd();
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
};




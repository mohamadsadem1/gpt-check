// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawVolume.generated.h"

UCLASS()
class MYPROJECT9_API ASpawVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawVolume();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
		class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Actor_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Actor_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Actor_3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Actor_4;
	TArray<TSubclassOf<AActor>>SpawnArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		int32 MaxEnemies = 5;


	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<AActor> EnemyClass;

	int32 NumSpawnedEnemies = 0;

	int32 NumAliveEnemies = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float MaxEnemiesAlive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Spawning")
		void SpawnEnemy();
	virtual void SpawnEnemy_Implementation();

	UFUNCTION()
		void OnEnemyKilled(AActor* DestroyedActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Spawning")
	TSubclassOf<class AActor> GetSpawnActor();

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetSpawnPoint();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Spawning")
	void SpawnOurPawn(UClass* ToSpawn, const FVector& Location);

	FTimerHandle SpawnTimer;

	int32 NumEnemies = 0;

	void SpawnNextEnemy(float Delay);
	FVector GetRandomSpawnLocation() const;

	UFUNCTION()
		void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

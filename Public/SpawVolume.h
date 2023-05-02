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

	/*
				SPAWNING LOGIC
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning | Logic")
	int32 NumberAlive;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning | Logic")
	int32 MaxNumberAlive;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning | Logic")
	int32 NumberEnemySpawned;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning | Logic")
	int32 MaxNumberEnmeySpawned;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning | Logic")
	bool bOverlapingWithVolumeBox;
	int32 Index1;


	/*
				ENEMIES TO SPAWN/ARRAY
	*/
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

	TArray<TSubclassOf<AActor>> SpawnArray;


	/*
				SPELL TO SPAWN/ARRAY
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Spell_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Spell_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Spell_3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TSubclassOf<AActor> Spell_4;

	TArray<TSubclassOf<AActor>>ItemArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray <class AEnemy*> EnemiesAliveArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	int32 arraysize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetSpawnPoint();

	UFUNCTION(BlueprintPure, Category = "Spawning")
	TSubclassOf<AActor> GetSpawnActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawning")
	void SpawnOurActor(UClass* ToSpawn, const FVector& Location);

	void OnEnemyDeath(AEnemy*Enemy);



	UFUNCTION(BlueprintCallable)
	virtual void VolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void VolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
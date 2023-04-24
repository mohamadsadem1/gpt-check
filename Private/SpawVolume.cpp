// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "collect.h"
#include "Enemy.h"

// Sets default values
ASpawVolume::ASpawVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));


	SpawnDelayMin = 1.0f;
	SpawnDelayMax = 5.0f;
	MaxEnemiesAlive = 5;

	NumAliveEnemies = 0;


}

// Called when the game starts or when spawned
void ASpawVolume::BeginPlay()
{
	Super::BeginPlay();

	SpawningBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawVolume::HandleOverlap);

	if (EnemyClass)
	{
		SpawnNextEnemy(0.0f);
	}

	if (Actor_1 && Actor_2 && Actor_3 && Actor_4)
	{
		SpawnArray.Add(Actor_1);
		SpawnArray.Add(Actor_2);
		SpawnArray.Add(Actor_3);
		SpawnArray.Add(Actor_4);
	}
}

// Called every frame
void ASpawVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawVolume::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent();
	FVector Origin = SpawningBox->GetComponentLocation();
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	return Point;
}
void ASpawVolume::SpawnOurPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;
		if (World) 
		{
			APawn *PawnSpawned = World->SpawnActor<APawn>(ToSpawn, Location, FRotator(0.f),SpawnParams);

		}
	}
}
TSubclassOf<AActor> ASpawVolume::GetSpawnActor()
{
	if (SpawnArray.Num() > 0)
	{
		int32 Selection = FMath::RandRange(0, SpawnArray.Num() - 1);

		return SpawnArray[Selection];
	}
	else
	{
		return nullptr;
	}
}

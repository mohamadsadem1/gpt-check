// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "AIController.h"
#include "collect.h"


// Sets default values
ASpawVolume::ASpawVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));

	bOverlapingWithVolumeBox = false;

	NumberAlive =  0;

	 NumberEnemySpawned = 0;

	 MaxNumberAlive = 5;

	 MaxNumberEnmeySpawned = 10;

	  Index1 = 0;




}

// Called when the game starts or when spawned
void ASpawVolume::BeginPlay()
{
	Super::BeginPlay();

	if (Actor_1 && Actor_2 && Actor_3 && Actor_4)
	{
		SpawnArray.Add(Actor_1);
		SpawnArray.Add(Actor_2);
		SpawnArray.Add(Actor_3);
		SpawnArray.Add(Actor_4);
	}

	SpawningBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawVolume::VolumeOnOverlapBegin);

	SpawningBox->OnComponentEndOverlap.AddDynamic(this, &ASpawVolume::VolumeOnOverlapEnd);


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

void ASpawVolume::SpawnOurActor_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;

		if (World)
		{
			if (arraysize < MaxNumberEnmeySpawned)
			{
				AActor* Actor = World->SpawnActor<AActor>(ToSpawn, Location, FRotator(0.f), SpawnParams);

				AEnemy* Enemy = Cast<AEnemy>(Actor);
				if (Enemy)
				{
					Enemy->SpawnDefaultController();

					AAIController* AICont = Cast<AAIController>(Enemy->GetController());
					if (AICont)
					{
						Enemy->AIController = AICont;

					}
					EnemiesAliveArray.Add(Enemy);

					arraysize = EnemiesAliveArray.Num();
					Enemy->IsSpawnedByVolume = true;

					NumberAlive++;

					NumberEnemySpawned++;
				}
			}
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

void  ASpawVolume::OnEnemyDeath(AEnemy* Enemy1)
{
	if (Enemy1)
	{
		EnemiesAliveArray.Remove(Enemy1);
	}
}

void ASpawVolume::VolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		bOverlapingWithVolumeBox = true;
	}


}

void ASpawVolume::VolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ 
	bOverlapingWithVolumeBox = false;


}






// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_MapGenerator.h"

#include <string>

// Sets default values
ATest_MapGenerator::ATest_MapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATest_MapGenerator::BeginPlay()
{
	Super::BeginPlay();
	GetInfoFromDataTable();
}

// Called every frame
void ATest_MapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATest_MapGenerator::GetInfoFromDataTable()
{
	if (TestTileDataTable != nullptr)
	{
		TArray<FTiles*> tiles;
		TestTileDataTable->GetAllRows("", tiles);
		for (const FTiles* Tile : tiles)
		{
			TestTilesArray.Add(*Tile);
		}
		
		if (!TestTilesArray.IsEmpty())
		{
			UE_LOG(LogTemp, Log, TEXT("Founded tile name is: %s"), *TestTilesArray[3].TileName.ToString());
		}
	}
}

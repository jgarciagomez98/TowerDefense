// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_MapGenerator.h"
#include "DrawDebugHelpers.h"

#include <string>

#include "Engine/StaticMeshActor.h"

// Sets default values
ATest_MapGenerator::ATest_MapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridSize = FIntVector2(5, 5);
	ShowDebugBox = false;
}

// Called when the game starts or when spawned
void ATest_MapGenerator::BeginPlay()
{
	Super::BeginPlay();
	GetInfoFromDataTable();
	GenerateGrid();
	//TODO: Collapse ONE random slot for test
	CollapseSlot();
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
			UE_LOG(LogTemp, Log, TEXT("Founded tile name is: %s"), *TestTilesArray[2].TileName.ToString());
		}
	}
}

void ATest_MapGenerator::GenerateGrid()
{
	for (int i = 0; i < GridSize.X; i++)
	{
		for (int j = 0; j < GridSize.Y; j++)
		{
			//Debug boxes for mesh bounds
			FVector DebugBoxLocation = FVector(GetActorLocation().X + i * 200, GetActorLocation().Y + j * 200, GetActorLocation().Z);
			if (ShowDebugBox)
			{
				DrawDebugBox(GetWorld(), DebugBoxLocation, FVector(100, 100, 100), FColor::Red, true, -1, 0, 2);
			}
			//Add slots to grid
			TestSlotsArray.Add(FSlots(TestTilesArray, DebugBoxLocation));
		}
	}
}

void ATest_MapGenerator::SpawnStaticMeshActors(const FVector& Location) const
{
	AStaticMeshActor* NewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	NewActor->SetMobility(EComponentMobility::Movable);
	NewActor->SetActorLocation(Location);
	if (UStaticMeshComponent* MeshComponent = NewActor->GetStaticMeshComponent())
	{
		MeshComponent->SetStaticMesh(TestTilesArray[FMath::RandRange(0, TestTilesArray.Num() - 1)].TileMesh);
	}
}

void ATest_MapGenerator::SpawnStaticMeshActors(const FVector& Location, const FTiles& SelectedTile) const
{
	AStaticMeshActor* NewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	NewActor->SetMobility(EComponentMobility::Movable);
	NewActor->SetActorLocation(Location);
	if (UStaticMeshComponent* MeshComponent = NewActor->GetStaticMeshComponent())
	{
		MeshComponent->SetStaticMesh(SelectedTile.TileMesh);
	}
}

void ATest_MapGenerator::CollapseSlot()
{
	FSlots SelectedSlotToCollapse = TestSlotsArray[FMath::RandRange(0, TestSlotsArray.Num() - 1)];
	FTiles SelectedTile = SelectedSlotToCollapse.Tiles[FMath::RandRange(0, SelectedSlotToCollapse.Tiles.Num() - 1)];
	SpawnStaticMeshActors(SelectedSlotToCollapse.SlotLocation, SelectedTile);
	//Remove all non selected tiles
	SelectedSlotToCollapse.Tiles.Remove(SelectedTile);
	// TArray<FTiles> AuxArray = SelectedSlotToCollapse.Tiles;
	//
	// for (FTiles Element : AuxArray)
	// {
	// 	if (Element.TileID != SelectedTile.TileID)
	// 	{
	// 		SelectedSlotToCollapse.Tiles.RemoveSwap(Element);
	// 	}
	// }
}

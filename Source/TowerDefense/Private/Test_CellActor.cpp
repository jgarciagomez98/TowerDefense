// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_CellActor.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ATest_CellActor::ATest_CellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_CellActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest_CellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATest_CellActor::DrawDebugBoxHelper(const FVector& DebugBoxSize) const
{
	const FVector DebugBoxLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	DrawDebugBox(GetWorld(), DebugBoxLocation, DebugBoxSize, FColor::Red, true, -1, 0, 2);
}

void ATest_CellActor::SetTileDataTable(UDataTable* DataTable)
{
	TileDataTable = DataTable;
}

void ATest_CellActor::InitializeCell()
{
	InitializeCell(TileDataTable);
}

void ATest_CellActor::InitializeCell(const UDataTable* DataTable)
{
	if (DataTable != nullptr)
	{
		int it = 0;
		TilesArray = GetTileDataFromDataTable(DataTable);
		for (const FTileStruct* Tile : TilesArray)
		{
			FVector Location = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + it * 200);
			SpawnStaticMeshActors(Location, *Tile);
			it++;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The tile data table in Cell actor class is null"));
	}
}

void ATest_CellActor::ClearAllSpawnedTiles()
{
	for (const FDebugTile* DebugTile : TilesMeshActorArray)
	{
		DebugTile->StaticMeshActor->Destroy();
	}
	//Clear all the array data 
	TilesMeshActorArray.Empty();
	TilesArray.Empty();
}

void ATest_CellActor::CollapseCell()
{
	//Remove the unselected tiles from array
	const FTileStruct* SelectedTile = TilesArray[FMath::RandRange(0, TilesArray.Num() - 1)];
	TArray<FTileStruct*> TempArray;
	for (FTileStruct* Tile : TilesArray)
	{
		if (Tile == SelectedTile)
		{
			TempArray.Add(Tile);
			break;
		}
	}
	TilesArray = TempArray;

	//Remove unselected spawned tiles
	for (FDebugTile* TilesMeshActor : TilesMeshActorArray)
	{
		if (TilesMeshActor->ID != SelectedTile->ID)
		{
			TilesMeshActor->StaticMeshActor->Destroy();
			// TilesMeshActorArray.Remove(TilesMeshActor);
		}
	}
	
}

TArray<FTileStruct*> ATest_CellActor::GetTileDataFromDataTable(const UDataTable* DataTable)
{
	TArray<FTileStruct*> Tiles;
	DataTable->GetAllRows("", Tiles);
	return Tiles;
}

void ATest_CellActor::SpawnStaticMeshActors(const FVector& Location, const FTileStruct& Tile)
{
	AStaticMeshActor* NewMeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	NewMeshActor->SetMobility(EComponentMobility::Movable);
	NewMeshActor->SetActorLocation(Location);
	if (UStaticMeshComponent* MeshComponent = NewMeshActor->GetStaticMeshComponent())
	{
		MeshComponent->SetStaticMesh(Tile.Mesh);
	}
	//Add new spawned mesh actor to array
	TilesMeshActorArray.Add(new FDebugTile(Tile.ID, NewMeshActor));
}


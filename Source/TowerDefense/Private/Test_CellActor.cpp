// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_CellActor.h"
#include "DrawDebugHelpers.h"
#include "WorldPartition/ContentBundle/ContentBundleLog.h"

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
		TilesArray = GetTileDataFromDataTable(DataTable);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The tile data table in Cell actor class is null"));
	}
}

TArray<FTileStruct*> ATest_CellActor::GetTileDataFromDataTable(const UDataTable* DataTable)
{
	TArray<FTileStruct*> Tiles;
	DataTable->GetAllRows("", Tiles);
	return Tiles;
}


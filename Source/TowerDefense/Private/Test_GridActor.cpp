// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_GridActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATest_GridActor::ATest_GridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridSize = FIntPoint(2, 2);
	//Debug variables
	ShowDebugBox = false;
	CellSize = FVector(100);

}

// Called when the game starts or when spawned
void ATest_GridActor::BeginPlay()
{
	Super::BeginPlay();
	// SpawnCells();
}

// Called every frame
void ATest_GridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATest_GridActor::GenerateGrid()
{
	//Before any regeneration clear all data
	ClearData();
	SpawnCells();
}

void ATest_GridActor::RemoveGrid()
{
	ClearData();
}

void ATest_GridActor::CollapseAllCells()
{
	TArray<ATest_CellActor*> TempArray = UnCollapsedCellActorsArray;
	if (!UnCollapsedCellActorsArray.IsEmpty())
	{
		for (int i = 0; i < TempArray.Num(); i++)
		{
			CollapseOneCell();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("All cells are collapsed"));
	}
	
	TempArray.Empty();
}

void ATest_GridActor::CollapseOneCell()
{
	if (!UnCollapsedCellActorsArray.IsEmpty())
	{
		//Find random cell and collapse
		const uint8 Index = FMath::RandRange(0, UnCollapsedCellActorsArray.Num() - 1);
		CollapseCell(UnCollapsedCellActorsArray[Index]);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("All cells are collapsed"));
	}
}

void ATest_GridActor::CollapseCell(ATest_CellActor* Cell)
{
	//Collapse cell
	Cell->CollapseCell();
	
	//Add collapsed cell to CollapsedCellActorsArray
	CollapsedCellActorsArray.Add(Cell);

	//Remove collapsed cell from UnCollapsedCellActorsArray
	UnCollapsedCellActorsArray.Remove(Cell);
}

void ATest_GridActor::SpawnCells()
{
	if (ActorToSpawn != nullptr)
	{
		for (int i = 0; i < GridSize.X; i++)
		{
			for (int j = 0; j < GridSize.Y; j++)
			{
				//Spawn cell actor
				FVector CellLocation = FVector(GetActorLocation().X + i  * (CellSize.X * 2), GetActorLocation().Y + j * (CellSize.Y * 2), GetActorLocation().Z);
				if (AActor* NewActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, CellLocation, FRotator(0.f,0.f,0.f)))
				{
					ATest_CellActor* NewCell = Cast<ATest_CellActor>(NewActor);
					NewCell->InitializeCell(TileDataTable);
					
					if (ShowDebugBox)
					{
						NewCell->DrawDebugBoxHelper(CellSize);
					}
					//Add cell to array
					UnCollapsedCellActorsArray.Add(NewCell);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("The new cell to spawn is not created"));
				}
			}
		}	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The actor to spawn for make grid is null"));
	}
}

void ATest_GridActor::ClearData()
{
	//Remove debug draw helpers
	FlushPersistentDebugLines(GetWorld());
	
	//Clear Cells array
	RemoveAllCellsFromWorld();
}

void ATest_GridActor::RemoveAllCellsFromWorld()
{
	//Remove cells from UnCollapsedCellActorsArray
	if (!UnCollapsedCellActorsArray.IsEmpty())
	{
		for (ATest_CellActor* Cell : UnCollapsedCellActorsArray)
		{
			Cell->ClearAllSpawnedTiles();
			Cell->Destroy();
		}
		UnCollapsedCellActorsArray.Empty();
	}

	//Remove cells from CollapsedCellActorsArray
	if (!CollapsedCellActorsArray.IsEmpty())
	{
		for (ATest_CellActor* Cell : CollapsedCellActorsArray)
		{
			Cell->ClearAllSpawnedTiles();
			Cell->Destroy();
		}
		CollapsedCellActorsArray.Empty();
	}
}


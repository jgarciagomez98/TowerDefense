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
				if (AActor* NewCell = GetWorld()->SpawnActor<AActor>(ActorToSpawn, CellLocation, FRotator(0.f,0.f,0.f)))
				{
					if (ShowDebugBox)
					{
						Cast<ATest_CellActor>(NewCell)->DrawDebugBoxHelper(CellSize);
					}
					//Add cell to array
					CellActorsArray.Add(Cast<ATest_CellActor>(NewCell));
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
	if (ShowDebugBox)
	{
		//Remove debug draw helpers
		FlushPersistentDebugLines(GetWorld());
	}

	//Clear Cells array
	RemoveAllCellsFromWorld();
	CellActorsArray.Empty();
}

void ATest_GridActor::RemoveAllCellsFromWorld()
{
	for (ATest_CellActor* Cell : CellActorsArray)
	{
		Cell->Destroy();
	}
}


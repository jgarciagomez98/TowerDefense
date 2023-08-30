// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefense/Public/MapGeneration_V2/GridGenerator.h"

#include "TowerDefense/Public/MapGeneration_V2/CellActor.h"

// Sets default values
AGridGenerator::AGridGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set default properties
	GridSize = FIntVector3(2, 2, 1);
	CellSize = FVector(100);
	bShowDebugBounds = false;

}

// Called when the game starts or when spawned
void AGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridGenerator::GenerateGrid()
{
	ClearData();
	SpawnCells();
}

void AGridGenerator::ClearGrid()
{
	ClearData();
}

void AGridGenerator::SpawnCells()
{
	for (int i = 0; i < GridSize.X; i++)
	{
		for (int j = 0; j < GridSize.Y; j++)
		{
			for (int k = 0; k < GridSize.Z; k++)
			{
				FVector CellLocation = FVector(
					GetActorLocation().X + i * (CellSize.X * 2),
					GetActorLocation().Y + j * (CellSize.Y * 2),
					(GetActorLocation().Z + CellSize.Z)+ k * (CellSize.Z * 2));
				if (AActor* NewActor = GetWorld()->SpawnActor<AActor>(ACellActor::StaticClass(), CellLocation, FRotator(0.f, 0.f, 0.f)))
				{
					ACellActor* NewCell = Cast<ACellActor>(NewActor);

					if (bShowDebugBounds)
					{
						NewCell->DrawDebugBounds(CellSize);
					}

					//Add new cells to array
					CellActorsArray.Add(NewCell);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("The new cell to spawn is not created"));
				}
			}
		}
	}
}

void AGridGenerator::ClearData()
{
	FlushPersistentDebugLines(GetWorld());

	if (!CellActorsArray.IsEmpty())
	{
		for (const auto Cell : CellActorsArray)
		{
			Cell->Destroy();
		}
		CellActorsArray.Empty();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cell actors array size: %d"), CellActorsArray.Num());
	}
}


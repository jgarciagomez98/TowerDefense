// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefense/Public/MapGeneration_V2/CellActor.h"

// Sets default values
ACellActor::ACellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

}

// Called when the game starts or when spawned
void ACellActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellActor::DrawDebugBounds(const FVector& CellSize) const
{
	const FVector DebugBoxLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	DrawDebugBox(GetWorld(), DebugBoxLocation, CellSize, FColor::Red, true, -1, 0, 2);
}

void ACellActor::InitializeCell()
{
	InitializeCell(FIntVector(0,0,0), {});
}

void ACellActor::InitializeCell(FIntVector GridIndex, const TArray<FTileStruct*>& TilesStructArray)
{
	GridPositionIndex = GridIndex;
	FillTilesArray(TilesStructArray);
}

void ACellActor::SetGridPositionIndex(FIntVector index)
{
	GridPositionIndex = index;
}

FIntVector ACellActor::GetGridPositionIndex() const
{
	return GridPositionIndex;
}

void ACellActor::ClearTiles()
{
	for (ATileActor* Tiles : TilesArray)
	{
		Tiles->Destroy();
	}
	TilesArray.Empty();
}

void ACellActor::FillTilesArray(TArray<FTileStruct*> TilesStructArray)
{
	for (FTileStruct* Tile : TilesStructArray)
	{
		ATileActor* NewTileActor = GetWorld()->SpawnActor<ATileActor>(ATileActor::StaticClass(),
				GetActorLocation(),
				FRotator(0,0,0));
		
		NewTileActor->SetTileProperties(Tile);
		TilesArray.Add(NewTileActor);
		
		if (Tile->RotationVariants > 0)
		{
			for (int i = 1; i <= Tile->RotationVariants; i++)
			{
				const FName TileName = FName(Tile->Name.ToString() + "_" + FString::FromInt(i));
				const FTileStruct* NewTileStruct =  new FTileStruct(Tile->ID, TileName, Tile->Mesh, Tile->RotationVariants, Tile->Sockets);
				
				NewTileActor = GetWorld()->SpawnActor<ATileActor>(ATileActor::StaticClass(),
				FVector(GetActorLocation().X, GetActorLocation().Y, (GetActorLocation().Z + 100) * i),
				FRotator(0,0,0));
				
				NewTileActor->SetTileProperties(NewTileStruct);
				NewTileActor->RotateTile(i);
				TilesArray.Add(NewTileActor);

				//Add tiles into a folder in world outliner
				NewTileActor->SetFolderPath("/Tiles");
			}
		}
		
		//Add tiles into a folder in world outliner
		NewTileActor->SetFolderPath("/Tiles");
	}
}


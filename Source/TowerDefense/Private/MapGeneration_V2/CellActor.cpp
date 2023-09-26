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

void ACellActor::CollapseCell()
{
	CollapseCell(ETileType::None);
}

bool ACellActor::GetIsCollapsed() const
{
	return IsCollapsed;
}

void ACellActor::ClearTiles()
{
	for (ATileActor* Tiles : TilesArray)
	{
		Tiles->Destroy();
	}
	TilesArray.Empty();
}

void ACellActor::CollapseCell(const ETileType TileType)
{
	if (!TilesArray.IsEmpty())
	{
		ATileActor* SelectedTile = nullptr;
		
		switch (TileType) {
		case ETileType::Spawn:
			//Create and place spawn tile in world
			for (const ATileActor* Tile : TilesArray)
			{
				if (Tile->GetTileType() == TileType)
				{
					SelectedTile = SpawnTileInWorld(Tile);
					break;
				}
			}
			
			//Remove all tiles from the array
			TilesArray.Empty();
			//Add the selected tile to the array
			TilesArray.Add(SelectedTile);
			
			//Add cells into a folder in world outliner
			SelectedTile->SetFolderPath("/Tiles");
			break;
		case ETileType::Target:
			break;
		case ETileType::Grass:
			break;
		case ETileType::Straight:
			break;
		case ETileType::Corner:
			break;
		case ETileType::Cross:
			break;
		case ETileType::Empty:
			break;
		case ETileType::None:
		default:
		
			break;
		}

		IsCollapsed = true;
	}
}

//////////////////////////////////
//PRIVATE METHODS
/////////////////////////////////
void ACellActor::FillTilesArray(TArray<FTileStruct*> TilesStructArray)
{
	for (FTileStruct* Tile : TilesStructArray)
	{
		ATileActor* NewTileActor = NewObject<ATileActor>();
		NewTileActor->SetTileProperties(Tile);
		TilesArray.Add(NewTileActor);
		
		if (Tile->RotationVariants > 0)
		{
			for (int i = 1; i <= Tile->RotationVariants; i++)
			{
				const FName TileName = FName(Tile->Name.ToString() + "_" + FString::FromInt(i));
				FTileStruct* NewTileStruct =  new FTileStruct(Tile->ID, TileName, Tile->Mesh, Tile->RotationVariants, Tile->Sockets, Tile->TileType);

				NewTileActor = NewObject<ATileActor>();
				
				NewTileActor->SetTileProperties(NewTileStruct);
				NewTileActor->RotateTile(i);
				TilesArray.Add(NewTileActor);
			}
		}
	}
}

ATileActor* ACellActor::SpawnTileInWorld(const ATileActor* Tile) const
{
	ATileActor* SpawnedTile = GetWorld()->SpawnActor<ATileActor>(ATileActor::StaticClass(),
					GetActorLocation(),
					FRotator(0,0,0));
	SpawnedTile->SetTileProperties(Tile->GetTileStruct());
	
	return SpawnedTile;
}


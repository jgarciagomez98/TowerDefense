// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_MapGenerator.h"
#include "DrawDebugHelpers.h"
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
	// CollapseSlot();
	CollapseGrid();
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
		for (FTiles* Tile : tiles)
		{
			TestTilesArray.Add(Tile);
		}
		
		if (!TestTilesArray.IsEmpty())
		{
			UE_LOG(LogTemp, Log, TEXT("Founded tile name is: %s"), *TestTilesArray[2]->TileName.ToString());
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
			TestSlotsArray.Add(new FSlots(TestTilesArray, DebugBoxLocation, FIntPoint(i, j)));

			//Add debug text from all possible tiles in each slot
			DebugRenderText(FString::FromInt(TestTilesArray.Num()),FVector(DebugBoxLocation.X, DebugBoxLocation.Y, DebugBoxLocation.Z + 100), FColor::White);
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
		MeshComponent->SetStaticMesh(TestTilesArray[FMath::RandRange(0, TestTilesArray.Num() - 1)]->TileMesh);
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
	if (!TestSlotsArray.IsEmpty())
	{
		const uint8 SelectedSlotIndex = FMath::RandRange(0, TestSlotsArray.Num() - 1);
	
		FSlots* SelectedSlotToCollapse = TestSlotsArray[SelectedSlotIndex];
		FTiles SelectedTile;
		if (!SelectedSlotToCollapse->Tiles.IsEmpty())
		{
			SelectedTile = *SelectedSlotToCollapse->Tiles[FMath::RandRange(0, SelectedSlotToCollapse->Tiles.Num() - 1)];
		}
		SpawnStaticMeshActors(SelectedSlotToCollapse->SlotLocation, SelectedTile);
	
		//Set the collapsed tile and remove all possibilities from tile array
		SelectedSlotToCollapse->CollapsedTile = SelectedTile;
		SelectedSlotToCollapse->Tiles.Empty();

		PropagateCollapsedSlotSelection(SelectedSlotToCollapse);

		//Change debug text render to collapsed slot
		DebugTextRenderArray[SelectedSlotIndex]->GetTextRender()->SetText(FText::FromString(FString::FromInt(SelectedSlotToCollapse->Tiles.Num())));
	
		//Add slot to collapsed slot array and remove from collapsable slots
		CollapsedSlotsArray.Add(SelectedSlotToCollapse);
		TestSlotsArray.Remove(SelectedSlotToCollapse);
	}
}

void ATest_MapGenerator::CollapseGrid()
{
	while (!TestSlotsArray.IsEmpty())
	{
		CollapseSlot();
	}
}

void ATest_MapGenerator::DebugRenderText(const FString& Text, const FVector Location, FColor Color)
{
	ATextRenderActor* PossibleTilesText = GetWorld()->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), Location, FRotator(90.f, 180.f, 0.f));
	PossibleTilesText->GetTextRender()->SetText(FText::FromString(Text));
	PossibleTilesText->GetTextRender()->SetTextRenderColor(Color);
	PossibleTilesText->SetActorScale3D(FVector(2.f, 2.f, 2.f));

	DebugTextRenderArray.Add(PossibleTilesText);
}

void ATest_MapGenerator::PropagateCollapsedSlotSelection(FSlots* CollapsedSlot)
{
	FIntPoint FoundSlotInGrid;
	//Find neighbours in X axis
	if (CollapsedSlot->GridIndex.X - 1 >= 0)
	{
		FoundSlotInGrid = FIntPoint(CollapsedSlot->GridIndex.X - 1, CollapsedSlot->GridIndex.Y);
		RemoveInvalidPossibilitiesFromNeighbourSlot(CollapsedSlot, GetFoundSlot(FoundSlotInGrid), NEGX);
	}
	if (CollapsedSlot->GridIndex.X + 1 <= TestSlotsArray.Num())
	{
		FoundSlotInGrid = FIntPoint(CollapsedSlot->GridIndex.X + 1, CollapsedSlot->GridIndex.Y);
		RemoveInvalidPossibilitiesFromNeighbourSlot(CollapsedSlot, GetFoundSlot(FoundSlotInGrid), POSX);
	}

	//Find neighbours in Y axis
	if (CollapsedSlot->GridIndex.Y - 1 >= 0)
	{
		FoundSlotInGrid = FIntPoint(CollapsedSlot->GridIndex.X, CollapsedSlot->GridIndex.Y - 1);
		RemoveInvalidPossibilitiesFromNeighbourSlot(CollapsedSlot, GetFoundSlot(FoundSlotInGrid), NEGY);
	}
	if (CollapsedSlot->GridIndex.Y + 1 <= TestSlotsArray.Num())
	{
		FoundSlotInGrid = FIntPoint(CollapsedSlot->GridIndex.X, CollapsedSlot->GridIndex.Y + 1);
		RemoveInvalidPossibilitiesFromNeighbourSlot(CollapsedSlot, GetFoundSlot(FoundSlotInGrid), POSY);
	}
}

void ATest_MapGenerator::RemoveInvalidPossibilitiesFromNeighbourSlot(FSlots* CollapsedSlot, FSlots* NeighbourSlot, EDirectionSockets DirectionSockets)
{
	if (NeighbourSlot != nullptr && CollapsedSlot != nullptr)
	{
		TArray<FTiles*> TempTilesArray = NeighbourSlot->Tiles;
		
		for (FTiles* Tiles : NeighbourSlot->Tiles)
		{
			switch (DirectionSockets)
			{ 
			case POSX:
				//First socket of the array
				if (!CollapsedSlot->CollapsedTile.Sockets[1].Equals(Tiles->Sockets[3]))
				{
					TempTilesArray.Remove(Tiles);
					UE_LOG(LogTemp, Log, TEXT("Remove Tiles from POSX Neighbour"));
				}	
				break;
			case NEGX:
				//Third socket of the array
				if (!CollapsedSlot->CollapsedTile.Sockets[3].Equals(Tiles->Sockets[1]))
				{
					TempTilesArray.Remove(Tiles);
					UE_LOG(LogTemp, Log, TEXT("Remove Tiles from NEGX Neighbour"));
				}	
				break;
			case POSY:
				//Second socket of the array
				if (!CollapsedSlot->CollapsedTile.Sockets[0].Equals(Tiles->Sockets[2]))
				{
					TempTilesArray.Remove(Tiles);
					UE_LOG(LogTemp, Log, TEXT("Remove Tiles from POSY Neighbour"));
				}	
				break;
			case NEGY:
				//Fourth socket of the array
				if (!CollapsedSlot->CollapsedTile.Sockets[2].Equals(Tiles->Sockets[0]))
				{
					TempTilesArray.Remove(Tiles);
					UE_LOG(LogTemp, Log, TEXT("Remove Tiles from NEGY Neighbour"));
				}	
				break;
			default: ;
			}	
		}

		//Set TempTilesArray to neighbour tiles to set the number of possibilities and clear TempTilesArray
		NeighbourSlot->Tiles = TempTilesArray;
		TempTilesArray.Empty();
		//Change number of possibilities of each slot
		DebugTextRenderArray[TestSlotsArray.Find(NeighbourSlot)]->GetTextRender()->SetText(FText::FromString(FString::FromInt(NeighbourSlot->Tiles.Num())));
	}
}

FSlots* ATest_MapGenerator::GetFoundSlot(const FIntPoint& IndexInGrid)
{
	for (FSlots* Neighbour : TestSlotsArray)
	{
		if (IndexInGrid == Neighbour->GridIndex)
		{
			return Neighbour;
		}
	}
	return nullptr;
}

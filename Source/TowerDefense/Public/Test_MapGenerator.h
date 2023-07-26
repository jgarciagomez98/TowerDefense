// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DataTable.h"
#include "Engine/TextRenderActor.h"
#include "GameFramework/Actor.h"
#include "Math/Vector2D.h"
#include "Test_MapGenerator.generated.h"

USTRUCT(BlueprintType)
struct FTiles : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TileID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TileName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* TileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HaveRotationVariants;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RotationVariants;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Sockets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ValidNeighbours;

	FTiles(): TileID(0), TileName(""), TileMesh(nullptr), HaveRotationVariants(false), RotationVariants(0){}
};

USTRUCT(BlueprintType)
struct FSlots
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SlotLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTiles CollapsedTile;
	TArray<FTiles*> Tiles;
	FIntPoint GridIndex;
	bool SlotCollapsed;
	

	FSlots(): GridIndex(), SlotCollapsed(false)
	{
	}

	FSlots(const TArray<FTiles*>& Tiles, const FVector& SlotLocation, const FIntPoint& GridIndex, const bool SlotCollapsed = false)
	{
		this->Tiles = Tiles;
		this->SlotLocation = SlotLocation;
		this->GridIndex = GridIndex;
		this->SlotCollapsed = SlotCollapsed;
	}
};

UENUM(BlueprintType)
enum EDirectionSockets { POSX, NEGX, POSY, NEGY };

UCLASS()
class TOWERDEFENSE_API ATest_MapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest_MapGenerator();

	//TODO: Test variables
	UPROPERTY(EditAnywhere)
	UDataTable* TestTileDataTable;
	UPROPERTY(EditAnywhere)
	FIntVector2 GridSize;
	UPROPERTY(EditAnywhere)
	bool ShowDebugBox;

	TArray<FTiles*> TestTilesArray;
	TArray<FSlots*> TestSlotsArray;
	TArray<FSlots*> CollapsedSlotsArray;

	TArray<ATextRenderActor*> DebugTextRenderArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetInfoFromDataTable();

	void GenerateGrid();

	void SpawnStaticMeshActors(const FVector& Location) const;

	void SpawnStaticMeshActors(const FVector& Location, const FTiles& SelectedTile) const;

	void CollapseSlot();

	void CollapseGrid();

	void DebugRenderText(const FString& Text, const FVector Location, FColor Color);

	void PropagateCollapsedSlotSelection(FSlots* CollapsedSlot);

	void RemoveInvalidPossibilitiesFromNeighbourSlot(FSlots* CollapsedSlot, FSlots* NeighbourSlot, EDirectionSockets DirectionSockets);

	FSlots* GetFoundSlot(const FIntPoint& IndexInGrid);
};

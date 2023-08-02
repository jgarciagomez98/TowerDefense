// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTileStruct.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Test_CellActor.generated.h"

USTRUCT(BlueprintType)
struct FDebugTile
{
	GENERATED_BODY()

	int32 ID;
	AStaticMeshActor* StaticMeshActor;

	FDebugTile(): ID(0), StaticMeshActor(){}
	FDebugTile(int32 ID, AStaticMeshActor* StaticMeshActor)
	{
		this->ID = ID;
		this->StaticMeshActor = StaticMeshActor;
	} 
};

UCLASS()
class TOWERDEFENSE_API ATest_CellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest_CellActor();
	
	TArray<FTileStruct*> TilesArray;
	TArray<FDebugTile*> TilesMeshActorArray;

private:
	UDataTable* TileDataTable;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DrawDebugBoxHelper(const FVector& DebugBoxSize) const;

	void SetTileDataTable(UDataTable* DataTable);

	void InitializeCell();

	void InitializeCell(const UDataTable* DataTable);

	void ClearAllSpawnedTiles();

	void CollapseCell();

private:
	TArray<FTileStruct*> GetTileDataFromDataTable(const UDataTable* DataTable);

	void SpawnStaticMeshActors(const FVector& Location, const FTileStruct& Tile);
};

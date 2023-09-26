// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellActor.h"
#include "FTileStruct.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GridGenerator.generated.h"

UCLASS()
class TOWERDEFENSE_API AGridGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridGenerator();

	UPROPERTY(EditAnywhere, Category="Grid generation")
	FIntVector GridSize;
	UPROPERTY(EditAnywhere, Category="Grid generation")
	FVector CellSize;
	UPROPERTY(EditAnywhere, Category="Grid generation")
	bool bShowDebugBounds;
	UPROPERTY(EditAnywhere, Category="Grid generation")
	UDataTable* TilesDataTable;

private:
	TArray<ACellActor*> CellActorsArray;
	TArray<FTileStruct*> TileStructArray;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, Category="Grid generation")
	void GenerateGrid();
	UFUNCTION(CallInEditor, Category="Grid generation")
	void ClearGrid();
	UFUNCTION(CallInEditor, Category="Grid generation")
	void CollapseGrid();

private:
	void SpawnCells();
	void ClearData();
	void GetTilesFromDataTable();
	void CollapseSpawnTile();
};

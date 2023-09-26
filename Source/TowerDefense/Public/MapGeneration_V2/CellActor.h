// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTileStruct.h"
#include "TileActor.h"
#include "GameFramework/Actor.h"
#include "CellActor.generated.h"

UCLASS()
class TOWERDEFENSE_API ACellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellActor();
	
	/**
	 * It's necessary to set default root if you want to spawn any actor using GetWorld()->SpawnActor in other class
	 */
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot;

private:
	FIntVector GridPositionIndex;
	//TODO: Remove UPROPERTY after testing
	UPROPERTY(VisibleAnywhere, Category="Tiles properties")
	TArray<ATileActor*> TilesArray;
	bool IsCollapsed;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DrawDebugBounds(const FVector& CellSize) const;

	void InitializeCell();
	
	void InitializeCell(FIntVector GridIndex, const TArray<FTileStruct*>& TilesStructArray);

	void SetGridPositionIndex(FIntVector index);

	FIntVector GetGridPositionIndex() const;

	void CollapseCell(ETileType TileType);

	void ClearTiles();

	void CollapseCell();

	bool GetIsCollapsed() const;

private:
	void FillTilesArray(TArray<FTileStruct*> TilesStructArray);

	ATileActor* SpawnTileInWorld(const ATileActor* Tile) const;

};

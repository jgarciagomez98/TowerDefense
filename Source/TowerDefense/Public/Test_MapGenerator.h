// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
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

	FTiles(): TileID(0), TileName(""), TileMesh(nullptr){}
};

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
	UPROPERTY(VisibleAnywhere)
	TArray<FTiles> TestTilesArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetInfoFromDataTable();

	void GenerateGrid();

	void SpawnStaticMeshActors(const FVector& Location) const;

};

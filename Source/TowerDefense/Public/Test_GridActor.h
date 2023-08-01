// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Test_CellActor.h"
#include "GameFramework/Actor.h"
#include "Test_GridActor.generated.h"

UCLASS()
class TOWERDEFENSE_API ATest_GridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest_GridActor();
	UPROPERTY(EditAnywhere, Category="Grid Generation")
	FIntPoint GridSize;
	UPROPERTY(EditAnywhere, Category="Grid Generation")
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, Category="Grid Generation")
	UDataTable* TileDataTable;
	
	//Debug variables
	UPROPERTY(EditAnywhere, Category="Grid Generation")
	bool ShowDebugBox;
	UPROPERTY(EditAnywhere, Category="Grid Generation")
	FVector CellSize;

private:
	TArray<ATest_CellActor*> CellActorsArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, Category="Grid Generation")
	void GenerateGrid();
	UFUNCTION(CallInEditor, Category="Grid Generation")
	void RemoveGrid();

private:

	void SpawnCells();

	void ClearData();

	void RemoveAllCellsFromWorld();
};

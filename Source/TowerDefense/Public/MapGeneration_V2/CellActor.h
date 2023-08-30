// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DrawDebugBounds(const FVector& CellSize) const;

	void InitializeCell();
	
	void InitializeCell(FIntVector GridIndex);

	void SetGridPositionIndex(FIntVector index);

	FIntVector GetGridPositionIndex() const;

};

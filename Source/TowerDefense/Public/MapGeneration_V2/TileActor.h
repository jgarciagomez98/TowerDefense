// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTileStruct.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

UCLASS()
class TOWERDEFENSE_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileActor();

private:
	FName TileName;
	UStaticMeshComponent* TileMesh;
	TArray<FString> TileSockets;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateTile(uint8 RotationVariants);
	
	void SetTileProperties(const FTileStruct* TileStruct);
	FName GetTileName() const;
	
};

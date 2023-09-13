// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneration_V2/TileActor.h"


// Sets default values
ATileActor::ATileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile mesh"));
	SetRootComponent(TileMesh);
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileActor::SetTileProperties(const FTileStruct* TileStruct)
{
	TileName = TileStruct->Name;
	TileMesh->SetStaticMesh(TileStruct->Mesh);
	TileMesh->SetWorldScale3D(FVector(10, 10, 10));
	TileSockets = TileStruct->Sockets;
}

FName ATileActor::GetTileName() const
{
	return TileName;
}


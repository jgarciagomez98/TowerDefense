// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefense/Public/MapGeneration_V2/CellActor.h"

// Sets default values
ACellActor::ACellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

}

// Called when the game starts or when spawned
void ACellActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellActor::DrawDebugBounds(const FVector& CellSize) const
{
	const FVector DebugBoxLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	DrawDebugBox(GetWorld(), DebugBoxLocation, CellSize, FColor::Red, true, -1, 0, 2);
}

void ACellActor::InitializeCell()
{
	InitializeCell(FIntVector(0,0,0));
}

void ACellActor::InitializeCell(FIntVector GridIndex)
{
	GridPositionIndex = GridIndex;
}

void ACellActor::SetGridPositionIndex(FIntVector index)
{
	GridPositionIndex = index;
}

FIntVector ACellActor::GetGridPositionIndex() const
{
	return GridPositionIndex;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefense/Public/MapGeneration_V2/GridGenerator.h"

// Sets default values
AGridGenerator::AGridGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


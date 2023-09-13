#pragma once

#include "Engine/DataTable.h"
#include "FTileStruct.generated.h"

USTRUCT(BlueprintType)
struct FTileStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RotationVariants;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Sockets;

	FTileStruct (): ID(0), Name(TEXT("")), Mesh(nullptr), RotationVariants(0)
	{
	}

	FTileStruct(int32 ID, FName Name, UStaticMesh* Mesh, int32 RotationVariants, TArray<FString> Sockets)
	{
		this->ID = ID;
		this->Name = Name;
		this->Mesh = Mesh;
		this->RotationVariants = RotationVariants;
		this->Sockets = Sockets;
	}
};

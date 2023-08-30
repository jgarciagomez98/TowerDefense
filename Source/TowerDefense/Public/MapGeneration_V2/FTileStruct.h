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
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTableExtractionDataLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UDataTableExtractionDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	template<class T>
	static TArray<T*> GetRowsFromDataTable(UDataTable* DataTable);
};

template <class T>
TArray<T*> UDataTableExtractionDataLibrary::GetRowsFromDataTable(UDataTable* DataTable)
{
	TArray<T*> Array;
	if (DataTable != nullptr)
	{
		DataTable->GetAllRows("", Array);
	}
	return Array;
}

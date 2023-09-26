#pragma once

#include "ETileType.generated.h"

UENUM(BlueprintType)
enum class ETileType
{
	None,
	Spawn,
	Target,
	Grass,
	Straight,
	Corner,
	Cross,
	Empty
};


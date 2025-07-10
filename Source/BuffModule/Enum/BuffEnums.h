#pragma once

UENUM(BlueprintType)
enum class EBuffTimeUpdate : uint8
{
	Add,
	Replace,
	Keep,
};

UENUM(BlueprintType)
enum class EBuffRemoveStackUpdate : uint8
{
	Clear,
	Reduce,
};

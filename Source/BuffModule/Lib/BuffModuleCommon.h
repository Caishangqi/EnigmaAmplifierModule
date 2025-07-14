// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BuffModuleCommon.generated.h"

class UBuffInstance;
class UBuffDefinition;
/**
 * @class UBuffModuleCommon
 * @brief Provides a set of utility functions to manage buffs on actors.
 *
 * This class includes functionality for adding and removing buffs from target actors,
 * allowing for dynamic manipulation of buffs during gameplay.
 *
 * Inherits from UBlueprintFunctionLibrary, enabling access to the functions in
 * Blueprints as callable utility functions.
 */
UCLASS()
class BUFFMODULE_API UBuffModuleCommon : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Buff")
	static bool AddBuff(TSubclassOf<UBuffDefinition> BuffDefinition, AActor* Target, AActor* Instigator = nullptr);
	UFUNCTION(BlueprintCallable, Category = Buff)
	static bool RemoveBuff(UBuffInstance* BuffInstance, AActor* Target, bool withProcedure = true);
};

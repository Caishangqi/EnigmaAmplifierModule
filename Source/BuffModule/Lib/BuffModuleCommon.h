// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BuffModuleCommon.generated.h"

class UBuffInstance;
class UBuffDefinition;
/**
 * 
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

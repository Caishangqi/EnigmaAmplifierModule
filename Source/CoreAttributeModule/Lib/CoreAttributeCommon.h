// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreAttributeCommon.generated.h"

struct FAttributeData;
class UCoreAttributeComponent;
/**
 * UCoreAttributeCommon serves as a utility class that provides common functionality for attributes
 * in the Core Attribute Module. This class inherits from UBlueprintFunctionLibrary, allowing the
 * implementation of static blueprint-callable functions.
 *
 * This class is part of the Core Attribute Module and can be utilized to define shared attribute-related
 * logic accessed across blueprints. It acts as a fundamental building block for attribute handling
 * within the module.
 */
UCLASS()
class COREATTRIBUTEMODULE_API UCoreAttributeCommon : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	static UCoreAttributeComponent* AppendAttribute(FAttributeData& appendedAttributeData, UObject* source, AActor* target);
	UFUNCTION(BlueprintPure, Category="Attribute")
	static FAttributeData GetFinalAttributeData(AActor* target);
	UFUNCTION(BlueprintPure, Category="Attribute")
	static FAttributeData GetBaseAttributeData(AActor* target);
	UFUNCTION(BlueprintCallable, Category="Attribute")
	static int GetAppendedAttributes(AActor* target, TArray<FAttributeData> &appendedAttributes);
};

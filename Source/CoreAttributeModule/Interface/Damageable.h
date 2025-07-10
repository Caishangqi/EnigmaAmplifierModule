// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttributeData.h"
#include "Damageable.generated.h"

struct FHitData;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Interface for objects that can take damage.
 *
 * The IDamageable interface defines the contract for classes that represent entities capable of receiving damage.
 * This interface should be inherited and implemented by any class that needs to handle damage-related functionality.
 * Users of this interface are expected to define the appropriate logic to process and handle damage in their implementations.
 */
class COREATTRIBUTEMODULE_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category="Data Provider")
	virtual bool SubmitHitData(FHitData& hitData) = 0;
	UFUNCTION(BlueprintCallable, Category="Data Provider")
	virtual bool AppendAttributeData(FAttributeData& AttributeData) = 0;

	UFUNCTION(BlueprintCallable, Category="Data Consumer")
	virtual FHitData& ConsumeHitData(FHitData& hitDataIn) = 0;
	UFUNCTION(BlueprintCallable, Category="Data Consumer")
	virtual FAttributeData& ConsumeAttributeData(FAttributeData& attributeDataIn) = 0;
};

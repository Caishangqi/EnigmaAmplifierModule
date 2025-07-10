// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BuffModel.generated.h"

struct FHitData;
class UBuffInstance;
class ACombatCharacter;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BUFFMODULE_API UBuffModel : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	AActor* OwnerCharacter = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	int32 StackBounceModifer = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UBuffInstance* OwnerBuffInstance = nullptr;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Logic)
	void Apply(UBuffInstance* BuffInstance);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Logic)
	void ConsumeHitData(UBuffInstance* BuffInstance, FHitData& hitDataIn);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BuffDefinition.generated.h"

enum class EBuffRemoveStackUpdate : uint8;
enum class EBuffTimeUpdate : uint8;
class UBuffInstance;
class UBuffModel;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BUFFMODULE_API UBuffDefinition : public UObject
{
	GENERATED_BODY()

public:
	/// Basic Information
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffBasic)
	int32 Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffBasic)
	FName BuffName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffBasic)
	FText Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffBasic)
	TObjectPtr<UTexture2D> Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffBasic)
	int32 Priority;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffBasic)
	int32 MaxStack;
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer Tags;*/
	/// Internal Value
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffInternal)
	TMap<FName, int32> InternalValue;
	/// Temporal Information
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffTemporal)
	bool bIsForever;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffTemporal)
	float Duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffTemporal)
	float TickTime;
	/// Update Methods
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffUpdate)
	EBuffTimeUpdate BuffTimeUpdate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BuffUpdate)
	EBuffRemoveStackUpdate BuffRemoveStackUpdate;

public:
	// Customize Buff Instance template, LD could storage additional variable and function.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BuffInstanceTemplate")
	TSubclassOf<UBuffInstance> BuffInstanceTemplate;

	/// Call back
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Buff Callback")
	TSubclassOf<UBuffModel> OnCreate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Buff Callback")
	TSubclassOf<UBuffModel> OnRemove;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Buff Callback")
	TSubclassOf<UBuffModel> OnTick;

	// Hit Process Methods, when Hit is valid and we apply and process HitData.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Buff Callback")
	TSubclassOf<UBuffModel> OnHitDataConsume;

	// Hit Receive Methods, when Hit is valid but we do not apply and process HitData yet.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Buff Callback")
	TSubclassOf<UBuffModel> OnHitReceive;
};

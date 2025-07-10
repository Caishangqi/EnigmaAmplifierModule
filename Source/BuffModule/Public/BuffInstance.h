// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BuffInstance.generated.h"

class ACombatCharacter;
class UBuffDefinition;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuffInstanceRemoved, UBuffInstance*, RemovedBuffInstance);

UCLASS(Blueprintable, BlueprintType)
class BUFFMODULE_API UBuffInstance : public UObject
{
	friend class UBuffComponent;
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Constructor")
	UBuffInstance* CreateFromDesc(UClass* definitionClass, AActor* instigator, AActor* target);
	UFUNCTION(BlueprintCallable, Category="Buff")
	UBuffInstance* MarkAsRemoved();

public:
	/// Buff Instance Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	UBuffDefinition* BuffDefinition = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	AActor* Instigator = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	AActor* Target = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	float Duration = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	float TickTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	int CurrentStack = 1;

	/// Call backs
	UPROPERTY(BlueprintAssignable)
	FBuffInstanceRemoved BuffInstanceRemoved;

private:
	UPROPERTY()
	bool IsRemoved = false;
};

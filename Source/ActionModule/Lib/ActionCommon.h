// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionCommon.generated.h"
enum class EActionType : uint8;
class UActionComponent;
struct FActionResult;
class UAction;
/**
 * A utility BlueprintFunctionLibrary providing common action handling functionality.
 * Contains static methods to manage lifecycle and queries of actions associated with an actor.
 * Methods within this class operate as helpers to interact with a UActionComponent attached to a specified actor.
 */
UCLASS()
class ACTIONMODULE_API UActionCommon : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult AddAction(AActor* componentOwner, TSubclassOf<UAction> actionClass);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult StartActionByName(AActor* instigator, FName actionName);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult StartActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult StartActionByType(AActor* instigator, EActionType type);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult StopActionByName(AActor* instigator, FName actionName);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult StopActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static FActionResult StopActionByType(AActor* instigator, EActionType type);
	UFUNCTION(BlueprintCallable, Category= Actions)
	static bool HasActionByType(AActor* componentOwner, EActionType type);

private:
	UFUNCTION(BlueprintCallable, Category= Actions)
	static UActionComponent* GetActionComponent(AActor* componentOwner);
};

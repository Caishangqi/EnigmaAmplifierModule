// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

enum class EActionType : uint8;
class UAction;


USTRUCT(BlueprintType)
struct FActionResult
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=ActionResultData)
	bool Success = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=ActionResultData)
	TObjectPtr<AActor> Instigator;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionInstantiated, UAction*, InstantiatedAction);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllActionInstantiated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStart, UAction*, StartAction, FActionResult, result);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStop, UAction*, StopAction, FActionResult, result);

///
/// 2022 Reworked GAS system
/// @details The Core Action Component for GAS, managing Actions and its life cycles,
/// it also expose several interface to Blueprints which make LD's life easier.
/// @author Caizii
/// @link https://github.com/Caishangqi/CharmingCraft/blob/main/Source/CharmingCraft/Core/Skill/CraftActionComponent.h @endlink 
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName= ActionAbilityComponent)
class ACTIONMODULE_API UActionComponent : public UActorComponent, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActionComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void                  GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual FGameplayTagContainer BP_GetOwnedGameplayTags() const override;
	virtual bool                  HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool                  HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

public:
	// When the Action is running / start, the correspond game-tags will added to the container
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Tags)
	FGameplayTagContainer ActiveGamePlayTags;
	// Runtime Action that was init when the Component load the Default action class templates
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Runtime)
	TArray<UAction*> Actions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Editor)
	TArray<TSubclassOf<UAction>> DefaultActions;

	UPROPERTY(BlueprintAssignable)
	FOnActionInstantiated OnActionInstantiated; // Call when action is Instantiated from class and added to list
	UPROPERTY(BlueprintAssignable)
	FOnAllActionInstantiated OnAllActionInstantiated; // Call when all actions are Instantiated from class
	UPROPERTY(BlueprintAssignable)
	FOnActionStart OnActionStart;
	UPROPERTY(BlueprintAssignable)
	FOnActionStop OnActionStop;

public:
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult AddAction(TSubclassOf<UAction> actionClass);
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult StartActionByName(AActor* instigator, FName actionName);
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult StartActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass);
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult StartActionByType(AActor* instigator, EActionType type);
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult StopActionByName(AActor* instigator, FName actionName);
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult StopActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass);
	UFUNCTION(BlueprintCallable, Category= Actions)
	FActionResult StopActionByType(AActor* instigator, EActionType type);
	UFUNCTION(BlueprintCallable, Category= Actions)
	bool HasActionByType(EActionType type);
};

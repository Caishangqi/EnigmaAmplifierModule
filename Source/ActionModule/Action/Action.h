// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "Action.generated.h"

class UActionComponent;
/**
 * 2022 Reworked GAS system
 * @details The UAction is the action of the ActionComponent executed object.
 * @author Caizii
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoolComplete, AActor*, InstigatorPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoolCStart, AActor*, InstigatorPawn);

UCLASS(Blueprintable, BlueprintType)
class ACTIONMODULE_API UAction : public UObject
{
	GENERATED_BODY()

	friend class UActionComponent;

public:
	UAction();
	virtual UWorld* GetWorld() const override;
	virtual bool    ImplementsGetWorld() const override;

public:
	// Action nickname to start/stop without a reference to the object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	FName ActionName;
	// Action Icon that used in skill bar and Hud
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> ActionIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action, meta = (AllowPrivateAccess = "true"))
	bool bIsCooling = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action)
	float CoolDown = 5.0f; // Default cooldown

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActionComponent> Owner; // Owner of the Action, usually the action Component
	// Tags added to owning actor when activated, removed when action stops
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;
	// Action can only start if OwningActor has none of these Tags applied
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> InstigatorActor;
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;
	// Whether or not the skill is running
	bool bIsRunning = false;
	// Timer
	FTimerHandle TimerHandle;

public:
	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	bool StartAction(AActor* instigator);
	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	bool CanActionStart(AActor* instigator);
	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	bool StopAction(AActor* instigator);

	UFUNCTION(BlueprintCallable, Category= "Action", BlueprintPure)
	bool IsRunning() const;
	UFUNCTION(BlueprintCallable, Category= "Timer")
	void StartCoolDown();
	UFUNCTION(BlueprintCallable, Category= "Timer")
	void HandleCooldownFinished();
	UFUNCTION(BlueprintCallable, Category= "Timer")
	void ResetCoolDown();
	UFUNCTION(BlueprintCallable, Category= "Timer")
	float GetRemainCooldown() const;

public:
	/// Events
	UPROPERTY(BlueprintAssignable)
	FOnCoolComplete OnCoolComplete;

	UPROPERTY(BlueprintAssignable)
	FOnCoolComplete OnCoolStart;
};

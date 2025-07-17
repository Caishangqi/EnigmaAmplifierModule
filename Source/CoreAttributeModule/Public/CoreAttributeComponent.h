// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeData.h"
#include "BuffComponent.h"
#include "CoreAttributeComponent.generated.h"

struct FHitData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterAttackEvent, ACharacter*, Instigator, ACharacter*, Victim);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitDataSubmitEvent, FHitData&, SubmittedHitData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeDataSubmitEvent, FAttributeData&, SubmittedAttributeData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COREATTRIBUTEMODULE_API UCoreAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCoreAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/// The wrapper function of ConsumeHitData, including the hit data submit event.
	/// @param hitDataIn The Hit Data that submitted.
	/// @return the Result Process/Consumed HitData that need to Apply to Attribute Data.
	UFUNCTION(BlueprintCallable, Category="Data Consumer")
	FHitData& SubmitHitData(FHitData& hitDataIn);

	/// When Hit Data Passed in, we will perform a task chain that calculate the damage formular
	/// and broadcast OnHitDataConsume Event. Buff could process this data again and modify it.
	/// The sequence of buff process this data is depended on Buff priority.
	///
	/// In Genera, ConsumeHitData will first pass the hitDataIn into buff module, buff would individually handle
	/// those data and the result hit data modified will pass through the damage formular then affect Attribute.
	/// @param hitDataIn The HitData that pass into the Attribute components, need process by damage formular.
	/// @return The Result Process/Consumed HitData that need to Apply to Attribute Data.
	FHitData& ConsumeHitData(FHitData& hitDataIn);

	/// The wrapper function of ConsumeAttributeData, including the attribute data submit event.
	/// @param attributeDataIn The Attribute Data you want to append.
	/// @return The Result Process/Consumed HitData that need to Apply to Attribute Data.
	UFUNCTION(BlueprintCallable, Category="Data Consumer")
	FAttributeData& SubmitAttributeData(FAttributeData& attributeDataIn);

	/// When The buff or action append the FAttributeData, it should append to AttributeDataCurrent, this process
	/// is not bother Buff Component. The Appended Data will invalid depends on Modes.
	///
	/// Modes:
	/// 1. Tick: Tick Mode will push the Appended data into a queue, when certain tick elapse the attribute will recalculate
	/// 2. Logic: Logic Mode will push the Appended data into a queue, when certain lifecycle of Buff and Action trigger, it will
	/// recalculate the attributes.
	///
	/// Remove appended AttributeData is triggered when a buff period end or when a action is end (depends on LD), removal of
	/// Attribute will reflect immediately when the mode is "LOGIC"
	/// @param attributeDataIn The AttributeData you want to append.
	/// @return The AttributeDataCurrent after Consume this attribute.
	FAttributeData& ConsumeAttributeData(FAttributeData& attributeDataIn);

	UFUNCTION(BlueprintCallable, Category="Utils")
	UBuffComponent* GetBuffComponent();

private:
	bool CalculateCurrentAttributeData();

	/// Buff Module Support
	
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attribute, meta = (AllowPrivateAccess = "true", ToolTip = "Owner base Attribute data"))
	FAttributeData AttributeDataBase; // LD could modify the base Attribute

private:
	UPROPERTY(VisibleAnywhere)
	FAttributeData AttributeDataCurrent; // Current Attribute Data that include Attribute Base + Append Attribute

	UPROPERTY()
	TArray<FAttributeData> AppendedAttributeData;

	UPROPERTY()
	TObjectPtr<UBuffComponent> CachedBuffComponent; // May invalid when character do not have Buff Component.

public:
	UPROPERTY(BlueprintAssignable, Category="Event")
	FCharacterAttackEvent CharacterAttackEvent;
	UPROPERTY(BlueprintAssignable, Category="Event")
	FHitDataSubmitEvent HitDataSubmitEvent;
	UPROPERTY(BlueprintAssignable, Category="Event")
	FAttributeDataSubmitEvent AttributeDataSubmitEvent;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

struct FHitData;
class UBuffDefinition;
class UBuffInstance;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuffAddToBuffList, UBuffInstance*, BuffInstance);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuffAddToBuffListRepeat, UBuffInstance*, BuffInstance);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName = "Buff Component"))
class BUFFMODULE_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBuffComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Set of Buff Info, if Buff Instance > 50 consider use link-list
	// and apply Quick Sort or Merge Sort
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	TArray<UBuffInstance*> BuffList;
	UPROPERTY()
	TArray<UBuffInstance*> PendingRemoveBuffList;

	UFUNCTION(Blueprintable, BlueprintCallable, Category = Buff)
	UBuffInstance* AddBuff(UBuffInstance* BuffInstance);
	void           UpdateBuffDuration(UBuffInstance* BuffInstance);
	void           TickBuffAndRemove(float DeltaTime);
	UFUNCTION(Blueprintable, BlueprintCallable, Category = Buff)
	UBuffInstance* RemoveBuff(UBuffInstance* BuffInstance);

	void SubmitPendingRemoveList(TArray<UBuffInstance*>& PendingRemoveList);

	UFUNCTION(Blueprintable, BlueprintCallable, Category = Buff)
	UBuffInstance* GetBuffInstanceByType(UBuffDefinition* buffTemplate);
	UFUNCTION(Blueprintable, BlueprintCallable, Category = Buff)
	bool GetHasBuff(UBuffDefinition* buffTemplate);
	/// Callbacks
	UPROPERTY(BlueprintAssignable)
	FBuffAddToBuffList BuffAddToBuffList;

	UPROPERTY(BlueprintAssignable)
	FBuffAddToBuffListRepeat BuffAddToBuffListRepeat;

	[[maybe_unused]] void ChainProcessHitData(FHitData& InHitData);

private:
	UBuffInstance* SearchBuff(int64 InternalId);
};

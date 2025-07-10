// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"

#include "BuffDefinition.h"
#include "BuffInstance.h"
#include "BuffModel.h"
#include "BuffModule.h"
#include "BuffModule/Enum/BuffEnums.h"

// operator that compare priority of BuffInstance base on int priority
struct FBuffInstancePriorityComparer
{
	bool operator()(const TObjectPtr<UBuffInstance>& A, const TObjectPtr<UBuffInstance>& B) const
	{
		return A->BuffDefinition->Priority < B->BuffDefinition->Priority;
	}
};

// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickBuffAndRemove(DeltaTime);
	// ...
}

UBuffInstance* UBuffComponent::AddBuff(UBuffInstance* BuffInstance)
{
	UBuffInstance* bi = SearchBuff(BuffInstance->BuffDefinition->Id);
	if (bi)
	{
		// Buff Already in the List
		if (bi->CurrentStack < bi->BuffDefinition->MaxStack)
		{
			bi->CurrentStack++;
			UpdateBuffDuration(bi);
			if (BuffInstance->BuffDefinition->OnCreate)
				BuffInstance->BuffDefinition->OnCreate.GetDefaultObject()->Apply(bi);
		}
		// Buff Already in the List and Current stack equal max stack allowed
		if (bi->CurrentStack == bi->BuffDefinition->MaxStack)
		{
			UpdateBuffDuration(bi);
		}
		BuffAddToBuffListRepeat.Broadcast(bi);
	}
	else
	{
		// Buff Do not in the List, we added it in
		BuffInstance->Duration = BuffInstance->BuffDefinition->Duration;
		if (BuffInstance->BuffDefinition->OnCreate)
			BuffInstance->BuffDefinition->OnCreate.GetDefaultObject()->Apply(BuffInstance);
		BuffList.Add(BuffInstance);
		// Order the BuffList based on Priority
		BuffList.Sort(FBuffInstancePriorityComparer());
		// Board cast new buff instance has add to the list
		BuffAddToBuffList.Broadcast(BuffInstance);
	}
	return nullptr;
}

void UBuffComponent::UpdateBuffDuration(UBuffInstance* BuffInstance)
{
	switch (BuffInstance->BuffDefinition->BuffTimeUpdate)
	{
	case EBuffTimeUpdate::Add:
		BuffInstance->Duration += BuffInstance->BuffDefinition->Duration;
		break;
	case EBuffTimeUpdate::Replace:
		BuffInstance->Duration = BuffInstance->BuffDefinition->Duration;
		break;
	case EBuffTimeUpdate::Keep: // Lazy, don't want to implemented
		break;
	}
}

void UBuffComponent::TickBuffAndRemove(float DeltaTime)
{
	TArray<UBuffInstance*> PendingRemove;
	PendingRemove.Reserve(BuffList.Num());

	for (UBuffInstance* BuffInstance : BuffList)
	{
		if (!BuffInstance) return;
		// Buff can tick
		if (BuffInstance->BuffDefinition->OnTick != nullptr)
		{
			if (BuffInstance->TickTime < 0) // Reach the tick time, we handle Tick
			{
				if (BuffInstance->BuffDefinition->OnTick)
					BuffInstance->BuffDefinition->OnTick.GetDefaultObject()->Apply(BuffInstance);
				BuffInstance->TickTime = BuffInstance->BuffDefinition->TickTime; // Reset the tick 
			}
			else
			{
				BuffInstance->TickTime -= DeltaTime; // Decrement the tick
			}
		}
		if (BuffInstance->Duration < 0 || BuffInstance->IsRemoved)
		{
			PendingRemove.Add(BuffInstance);
		}
		else
		{
			BuffInstance->Duration -= DeltaTime;
		}
	}
	// Collect and remove
	for (UBuffInstance* Instance : PendingRemove)
	{
		RemoveBuff(Instance);
	}
	for (UBuffInstance* RemoveBuffList : PendingRemoveBuffList)
	{
		if (BuffList.Contains(RemoveBuffList))
		{
			BuffList.Remove(RemoveBuffList);
		}
	}
}

UBuffInstance* UBuffComponent::RemoveBuff(UBuffInstance* BuffInstance)
{
	if (BuffInstance->IsRemoved)
	{
		BuffInstance->BuffInstanceRemoved.Broadcast(BuffInstance);
		BuffList.Remove(BuffInstance);
	}

	switch (BuffInstance->BuffDefinition->BuffRemoveStackUpdate)
	{
	case EBuffRemoveStackUpdate::Clear:
		if (BuffInstance->BuffDefinition->OnRemove)
			BuffInstance->BuffDefinition->OnRemove.GetDefaultObject()->Apply(BuffInstance);
		UE_LOG(LogBuffModule, Display, TEXT(" Remove Buff Instance: %s from : %s"), *BuffInstance->BuffDefinition->BuffName.ToString(), *GetOwner()->GetName())
		BuffInstance->BuffInstanceRemoved.Broadcast(BuffInstance); // Broadcast Remove event that UI knows it
		BuffList.Remove(BuffInstance);
		break;
	case EBuffRemoveStackUpdate::Reduce:
		BuffInstance->CurrentStack--;
		UE_LOG(LogBuffModule, Display, TEXT(" Reduce Buff Instance: %s stack. Current Stack : %d"), *BuffInstance->BuffDefinition->BuffName.ToString(), BuffInstance->CurrentStack)
		if (BuffInstance->BuffDefinition->OnRemove)
			BuffInstance->BuffDefinition->OnRemove.GetDefaultObject()->Apply(BuffInstance);
		if (BuffInstance->CurrentStack <= 0)
		{
			BuffInstance->BuffInstanceRemoved.Broadcast(BuffInstance);
			BuffList.Remove(BuffInstance);
		}
		else
		{
			BuffInstance->Duration = BuffInstance->BuffDefinition->Duration; // After decrement stack, we reset it
		}
	}
	return nullptr;
}

void UBuffComponent::SubmitPendingRemoveList(TArray<UBuffInstance*>& PendingRemoveList)
{
	PendingRemoveBuffList.Append(PendingRemoveList);
}

UBuffInstance* UBuffComponent::GetBuffInstanceByType(UBuffDefinition* buffTemplate)
{
	for (UBuffInstance* BuffInstance : BuffList)
	{
		if (BuffInstance->BuffDefinition == buffTemplate)
		{
			return BuffInstance;
		}
	}
	return nullptr;
}

bool UBuffComponent::GetHasBuff(UBuffDefinition* buffTemplate)
{
	if (GetBuffInstanceByType(buffTemplate))
	{
		return true;
	}
	return false;
}

UBuffInstance* UBuffComponent::SearchBuff(int64 InternalId)
{
	for (UBuffInstance* Instance : BuffList)
	{
		if (Instance->BuffDefinition->Id == InternalId)
		{
			return Instance;
		}
	}
	return nullptr;
}

void UBuffComponent::ChainProcessHitData(FHitData& InHitData)
{
	// TODO: Need ensure the buff list is sorted before process.
	for (UBuffInstance* List : BuffList)
	{
		if (List->BuffDefinition->OnHitDataConsume != nullptr)
			List->BuffDefinition->OnHitDataConsume.GetDefaultObject()->ConsumeHitData(List, InHitData);
	}
}

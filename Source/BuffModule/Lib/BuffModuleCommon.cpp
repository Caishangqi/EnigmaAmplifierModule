// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffModuleCommon.h"

#include "BuffComponent.h"
#include "BuffDefinition.h"
#include "BuffInstance.h"
#include "BuffModel.h"
#include "BuffModule.h"

/**
 * Adds a buff to the specified target actor.
 *
 * This method creates a new BuffInstance based on the provided BuffDefinition
 * and associates it with the target actor. The buff is applied to the target's
 * BuffComponent, if available. A log message is displayed upon successful addition.
 *
 * @param BuffDefinition The class of the buff definition that describes the buff to be added.
 * @param Target The actor to which the buff will be applied.
 * @param Instigator The actor responsible for applying the buff (optional).
 * @return Returns true if the buff was successfully added to the target, false otherwise.
 */
bool UBuffModuleCommon::AddBuff(TSubclassOf<UBuffDefinition> BuffDefinition, AActor* Target, AActor* Instigator)
{
	if (!BuffDefinition || Target)
	{
		UE_LOG(LogBuffModule, Error, TEXT("Could not all buff because the BuffDefinition or Target is null"));
		return false;
	}

	UBuffInstance* BuffInstance = nullptr;
	// We check whether we have the custom BuffInstance class
	if (BuffDefinition.GetDefaultObject()->BuffInstanceTemplate)
	{
		// We have the custom class, so we use the class to create specific Buff Instance
		UClass* classTemplate = BuffDefinition.GetDefaultObject()->BuffInstanceTemplate.Get();
		BuffInstance          = NewObject<UBuffInstance>(Target, classTemplate);
	}
	else
	{
		BuffInstance = NewObject<UBuffInstance>(Target, UBuffInstance::StaticClass());
	}
	BuffInstance->CreateFromDesc(BuffDefinition, Instigator, Target);
	UBuffComponent* comp = Cast<UBuffComponent>(Target->GetComponentByClass(UBuffComponent::StaticClass()));
	if (comp && BuffInstance)
	{
		comp->AddBuff(BuffInstance);
		UE_LOG(LogBuffModule, Display, TEXT("%s add buff %s to target: %s"), *Instigator->GetName(), *BuffInstance->BuffDefinition->BuffName.ToString(), *Target->GetName());
		return true;
	}
	return false;
}

/**
 * Removes a specified buff instance from the target actor.
 *
 * This method attempts to remove a provided BuffInstance from the associated
 * BuffComponent of the given target actor. If `withProcedure` is true, the
 * BuffInstance is marked as removed. If the conditions are not met (such as
 * the target lacking a BuffComponent or the BuffInstance being null), no
 * action is taken.
 *
 * @param BuffInstance The instance of the buff to be removed.
 * @param Target The actor from which the buff should be removed.
 * @param withProcedure Indicates whether the removal process should mark
 *        the BuffInstance as removed with additional logic.
 * @return Returns true if the buff was successfully marked as removed,
 *         false otherwise.
 */
bool UBuffModuleCommon::RemoveBuff(UBuffInstance* BuffInstance, AActor* Target, bool withProcedure)
{
	UBuffComponent* comp = Cast<UBuffComponent>(Target->GetComponentByClass(UBuffComponent::StaticClass()));
	if (comp && BuffInstance)
	{
		if (withProcedure)
		{
			BuffInstance->MarkAsRemoved();
			return true;
		}
	}
	return false;
}

bool UBuffModuleCommon::GetHasBuff(AActor* componentOwner, UBuffDefinition* buffTemplate)
{
	return GetBuffComponent(componentOwner)->GetHasBuff(buffTemplate);
}

UBuffComponent* UBuffModuleCommon::GetBuffComponent(AActor* componentOwner)
{
	UBuffComponent* comp = Cast<UBuffComponent>(componentOwner->GetComponentByClass(UBuffComponent::StaticClass()));
	if (comp)
		return comp;
	else
	{
		FMessageLog("Blueprint").Warning()
		                        ->AddToken(FTextToken::Create(FText::FromString(TEXT("Can not find the Buff Component"))));
		return nullptr;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffModuleCommon.h"

#include "BuffComponent.h"
#include "BuffDefinition.h"
#include "BuffInstance.h"
#include "BuffModel.h"
#include "BuffModule.h"

bool UBuffModuleCommon::AddBuff(TSubclassOf<UBuffDefinition> BuffDefinition, AActor* Target, AActor* Instigator)
{
	UBuffInstance* BuffInstance = NewObject<UBuffInstance>(Target, UBuffInstance::StaticClass());
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

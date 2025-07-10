// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffInstance.h"

#include "BuffDefinition.h"

UBuffInstance* UBuffInstance::CreateFromDesc(UClass* definitionClass, AActor* instigator, AActor* target)
{
	BuffDefinition = Cast<UBuffDefinition>(definitionClass->GetDefaultObject());
	Instigator     = instigator;
	Target         = target;
	Duration       = BuffDefinition->Duration;
	TickTime       = BuffDefinition->TickTime;
	return this;
}

UBuffInstance* UBuffInstance::MarkAsRemoved()
{
	IsRemoved    = true;
	CurrentStack = 0;
	Duration     = 0;
	TickTime     = 0;
	return this;
}

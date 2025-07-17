// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCommon.h"
#include "ActionComponent.h"

FActionResult UActionCommon::AddAction(AActor* componentOwner, TSubclassOf<UAction> actionClass)
{
	return GetActionComponent(componentOwner)->AddAction(actionClass);
}

FActionResult UActionCommon::StartActionByName(AActor* instigator, FName actionName)
{
	return GetActionComponent(instigator)->StartActionByName(instigator, actionName);
}

FActionResult UActionCommon::StartActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass)
{
	return GetActionComponent(instigator)->StartActionByClass(instigator, actionClass);
}

FActionResult UActionCommon::StartActionByType(AActor* instigator, EActionType type)
{
	return GetActionComponent(instigator)->StartActionByType(instigator, type);
}

FActionResult UActionCommon::StopActionByName(AActor* instigator, FName actionName)
{
	return GetActionComponent(instigator)->StopActionByName(instigator, actionName);
}

FActionResult UActionCommon::StopActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass)
{
	return GetActionComponent(instigator)->StopActionByClass(instigator, actionClass);
}

FActionResult UActionCommon::StopActionByType(AActor* instigator, EActionType type)
{
	return GetActionComponent(instigator)->StopActionByType(instigator, type);
}

bool UActionCommon::HasActionByType(AActor* componentOwner, EActionType type)
{
	return GetActionComponent(componentOwner)->HasActionByType(type);
}

UActionComponent* UActionCommon::GetActionComponent(AActor* componentOwner)
{
	UActionComponent* comp = Cast<UActionComponent>(componentOwner->GetComponentByClass(UActionComponent::StaticClass()));
	if (comp)
		return comp;
	else
	{
		FMessageLog("Blueprint").Warning()
		                        ->AddToken(FTextToken::Create(FText::FromString(TEXT("Can not find the Action Component"))));
		return nullptr;
	}
}

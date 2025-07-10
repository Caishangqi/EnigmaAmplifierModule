// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"

#include "ActionModule/Action/Action.h"


// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UAction>& Class : DefaultActions)
	{
		if (Class)
		{
			AddAction(Class); // Add each action to the list
		}
	}
	OnAllActionInstantiated.Broadcast();
}

void UActionComponent::OnRegister()
{
	Super::OnRegister();
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActionComponent::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
}

FActionResult UActionComponent::AddAction(TSubclassOf<UAction> actionClass)
{
	FActionResult actionResult;

	if (!ensure(actionClass))
		return actionResult;

	TObjectPtr<UAction> actionInstance = NewObject<UAction>(this, actionClass);
	actionInstance->Owner              = this;
	if (!ensure(actionInstance))
		return actionResult;
	else
	{
		Actions.Add(actionInstance);
		OnActionInstantiated.Broadcast(actionInstance);
		actionResult.Success = true;
	}

	return actionResult;
}

FActionResult UActionComponent::StartActionByName(AActor* instigator, FName actionName)
{
	FActionResult actionResult;

	for (UAction* Action : Actions)
	{
		if (IsValid(Action) && Action->ActionName == actionName)
		{
			if (Action->CanActionStart(instigator))
			{
				Action->StartAction(instigator);
				actionResult.Success = true;
				OnActionStart.Broadcast(Action, actionResult);
				return actionResult;
			}
			else
			{
				OnActionStart.Broadcast(Action, actionResult);
			}
		}
	}
	return actionResult;
}

FActionResult UActionComponent::StartActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass)
{
	FActionResult actionResult;
	UAction*      classObj = actionClass->GetDefaultObject<UAction>();
	if (classObj)
	{
		return StartActionByName(instigator, classObj->ActionName);
	}
	return actionResult;
}

FActionResult UActionComponent::StartActionByType(AActor* instigator, EActionType type)
{
	FActionResult actionResult;
	/// TODO: Add action type when the project progress
	return actionResult;
}

FActionResult UActionComponent::StopActionByName(AActor* instigator, FName actionName)
{
	FActionResult actionResult;
	for (UAction* Action : Actions)
	{
		if (IsValid(Action) && Action->ActionName == actionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(instigator);
				actionResult.Success = true;
				OnActionStop.Broadcast(Action, actionResult);
				return actionResult;
			}
			else
			{
				OnActionStop.Broadcast(Action, actionResult);
			}
		}
	}
	return actionResult;
}

FActionResult UActionComponent::StopActionByClass(AActor* instigator, TSubclassOf<UAction> actionClass)
{
	FActionResult actionResult;
	UAction*      classObj = actionClass->GetDefaultObject<UAction>();
	if (classObj)
	{
		return StopActionByName(instigator, classObj->ActionName);
	}
	return actionResult;
}

FActionResult UActionComponent::StopActionByType(AActor* instigator, EActionType type)
{
	FActionResult actionResult;
	return actionResult;
}

bool UActionComponent::HasActionByType(EActionType type)
{
	return true;
}

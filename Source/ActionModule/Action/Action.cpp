// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

#include "ActionComponent.h"
#include "ActionModule.h"

UAction::UAction()
{
}

bool UAction::IsRunning() const
{
	return bIsRunning;
}

void UAction::StartCoolDown()
{
	if (CoolDown >= 0.f)
	{
		bIsCooling = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAction::HandleCooldownFinished, CoolDown);
		OnCoolStart.Broadcast(InstigatorActor);
	}
}

void UAction::HandleCooldownFinished()
{
	bIsCooling = false;
	bIsRunning = false;
	ResetCoolDown();
	OnCoolComplete.Broadcast(InstigatorActor);
}

void UAction::ResetCoolDown()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

float UAction::GetRemainCooldown() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle);
}

/**
 * Determines if the action's associated owner supports the GetWorld functionality.
 *
 * This method verifies if the action's owner is valid and thus capable of returning a world context.
 *
 * @return True if the action's owner is valid and a world context can be retrieved; false otherwise.
 */
bool UAction::ImplementsGetWorld() const
{
	if (Owner == nullptr)
	{
		return false;
	}
	return true;
}

/**
 * Gets the world context in which the action's owner exists, if available.
 *
 * This method retrieves the UWorld instance associated with the Action's owner,
 * typically required for operations that need a reference to the game world.
 *
 * @return The UWorld instance for the action's owner. Returns nullptr if the owner is not set or unavailable.
 */
UWorld* UAction::GetWorld() const
{
	if (Owner == nullptr)
	{
		return nullptr;
	}
	return Owner->GetWorld();
}

bool UAction::StopAction_Implementation(AActor* instigator)
{
	bIsRunning = false;
	return true;
}

bool UAction::CanActionStart_Implementation(AActor* instigator)
{
	if (IsRunning())
		return false;

	UActionComponent* actionComp = Cast<UActionComponent>(GetOuter());
	if (actionComp->ActiveGamePlayTags.HasAny(BlockedTags))
	{
		// Check the Component tags, if have the block tags we return false
		return false;
	}
	return true;
}

bool UAction::StartAction_Implementation(AActor* instigator)
{
	UE_LOG(LogActionModule, Log, TEXT("Running Action: %s"), *ActionName.ToString())
	StartCoolDown();
	UActionComponent* actionComp = Cast<UActionComponent>(GetOuter());
	actionComp->ActiveGamePlayTags.AppendTags(GrantsTags);
	InstigatorActor = instigator;
	bIsRunning      = true;
	return true;
}

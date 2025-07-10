// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAttributeComponent.h"
#include "CoreAttributeModule.h"
#include "HitData.h"


// Sets default values for this component's properties
UCoreAttributeComponent::UCoreAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoreAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	GetBuffComponent(); // Set the buff component
	// ...
}


// Called every frame
void UCoreAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FHitData& UCoreAttributeComponent::SubmitHitData(FHitData& hitDataIn)
{
	HitDataSubmitEvent.Broadcast(hitDataIn); // We first broadcast the event to the other components
	return ConsumeHitData(hitDataIn); // We start consume the hitdata.
}

FHitData& UCoreAttributeComponent::ConsumeHitData(FHitData& hitDataIn)
{
	if (!hitDataIn.IsValidHit) return hitDataIn; // InValid Hit, we just return the hit data.
	UBuffComponent* BuffComponent = GetBuffComponent();
	if (!BuffComponent)
	{
		// We do not have the Buff Component on the player, we just calculate the damage.
		// TODO: We need to add the damage formula function call.
	}
	if (BuffComponent)
	{
		// We start process each hitData handler in the BuffInstances.
		BuffComponent->ChainProcessHitData(hitDataIn);
	}
	// TODO: Process HitData withing Attributes, submit final attributes

	return hitDataIn;
}

FAttributeData& UCoreAttributeComponent::SubmitAttributeData(FAttributeData& attributeDataIn)
{
	AttributeDataSubmitEvent.Broadcast(attributeDataIn); // We first broadcast the event to the other components
	return ConsumeAttributeData(attributeDataIn); // We start consume the attribute data.
}

FAttributeData& UCoreAttributeComponent::ConsumeAttributeData(FAttributeData& attributeDataIn)
{
	return AttributeDataCurrent;
}

UBuffComponent* UCoreAttributeComponent::GetBuffComponent()
{
	CachedBuffComponent = GetOwner()->GetComponentByClass<UBuffComponent>();
	if (!CachedBuffComponent)
		UE_LOG(LogCoreAttributeModule, Error, TEXT("Parent Character do not have Buff Component."))
	return CachedBuffComponent;
}

bool UCoreAttributeComponent::CalculateCurrentAttributeData()
{
	return false;
}

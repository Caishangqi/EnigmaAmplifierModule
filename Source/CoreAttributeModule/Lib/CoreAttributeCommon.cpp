// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAttributeCommon.h"

#include "AttributeData.h"
#include "CoreAttributeComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UCoreAttributeComponent* UCoreAttributeCommon::AppendAttribute(FAttributeData& appendedAttributeData, UObject* source, AActor* target)
{
	UCoreAttributeComponent* attributeComponent = Cast<UCoreAttributeComponent>(target->GetComponentByClass(UCoreAttributeComponent::StaticClass()));
	if (attributeComponent == nullptr)
	{
		FMessageLog("Blueprint").Warning()
		                        ->AddToken(FTextToken::Create(FText::FromString(TEXT("Can not find the CoreAttributeComponent in the target actor"))));
		return nullptr;
	}
	if (source == nullptr)
	{
		FMessageLog("Blueprint").Error()
		                        ->AddToken(FTextToken::Create(FText::FromString(TEXT("Source can not be null, the appended data need source"))));
	}

	if (appendedAttributeData.Source != source)
		appendedAttributeData.Source = source;
	attributeComponent->SubmitAttributeData(appendedAttributeData);
	return attributeComponent;
}

FAttributeData UCoreAttributeCommon::GetFinalAttributeData(AActor* target)
{
	FAttributeData           finalAttributeData;
	UCoreAttributeComponent* attributeComponent = Cast<UCoreAttributeComponent>(target->GetComponentByClass(UCoreAttributeComponent::StaticClass()));
	if (attributeComponent == nullptr)
	{
		FMessageLog("Blueprint").Warning()
		                        ->AddToken(FTextToken::Create(FText::FromString(TEXT("Can not find the CoreAttributeComponent in the target actor"))));
		return finalAttributeData;
	}

	return finalAttributeData;
}

FAttributeData UCoreAttributeCommon::GetBaseAttributeData(AActor* target)
{
	FAttributeData baseAttributeData;
	return baseAttributeData;
}

int UCoreAttributeCommon::GetAppendedAttributes(AActor* target, TArray<FAttributeData> &appendedAttributes)
{
	return 0;
}

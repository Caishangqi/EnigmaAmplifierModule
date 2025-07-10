// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBuffIndicator.generated.h"

class UBuffInstance;
/**
 * UWidgetBuffIndicator hold current displaying buff instance and display the buff graphic
 * information to user, the widget component need add to BuffHudWidgetComponent in order to
 * display multiple buffs and its remain and stacks.
 * @author Caizii
 */
UCLASS(Blueprintable, BlueprintType, DisplayName="Buff Indicator Widget")
class BUFFMODULE_API UWidgetBuffIndicator : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= Internal)
	TObjectPtr<UBuffInstance> CachedBuffInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Buff)
	TObjectPtr<UTexture2D> BuffIcon;

public:

	virtual void NativeOnInitialized() override;
	virtual void BeginDestroy() override;
};

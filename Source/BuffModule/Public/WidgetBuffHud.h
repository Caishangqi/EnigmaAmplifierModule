// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBuffHud.generated.h"
class UBuffComponent;
/**
 * Buff hud Widget management num of UWidgetBuffIndicator in a designed specific format in blueprints
 * The Widget will refer to an specific BuffModule when the BuffModule Component creates the UWidgetBuffHud Component.
 * @author Caizii
 */
UCLASS(Blueprintable, BlueprintType, DisplayName="Buff Hud Widget")
class BUFFMODULE_API UWidgetBuffHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= Internal)
	TObjectPtr<UBuffComponent> RefBuffComponent;

public:
	virtual void NativeOnInitialized() override;
	virtual void BeginDestroy() override;

public:
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WdigetActionIndicator.generated.h"

class UAction;
/**
 * UActionIndicator is the individual skill widget that display the current binding Action
 * information such as Cooldown, Action Icon, Action Stack etc. It also handle user mouse click
 * and hover event.
 * @author Caizii
 */
UCLASS(Blueprintable, BlueprintType, DisplayName="Action Indicator Widget")
class ACTIONMODULE_API UWidgetActionIndicator : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= Internal)
	TObjectPtr<UAction> CachedActionInstance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Action)
	TObjectPtr<UTexture2D> ActionIcon;

public:

	virtual void NativeOnInitialized() override;
	virtual void BeginDestroy() override;
};

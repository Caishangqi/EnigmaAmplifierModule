#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
DECLARE_LOG_CATEGORY_EXTERN(LogGameCommonModule, Log, All);

class FGameCommonModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	FString Author     = "C34 Teal Group";
	FString Maintainer = "Caizii";
};

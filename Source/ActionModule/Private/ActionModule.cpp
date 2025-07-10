#include "ActionModule.h"

#define LOCTEXT_NAMESPACE "FActionModule"
DEFINE_LOG_CATEGORY(LogActionModule);

void FActionModule::StartupModule()
{
	UE_LOG(LogActionModule, Display, TEXT("Game Ability Module Startup, Maintainer: %s"), *Author);
}

void FActionModule::ShutdownModule()
{
	UE_LOG(LogActionModule, Display, TEXT("Game Ability Module Shutdown, Have a nice day"))
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FActionModule, ActionModule)

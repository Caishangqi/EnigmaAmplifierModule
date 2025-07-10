#include "GameCommonModule.h"

#define LOCTEXT_NAMESPACE "FGameCommonModule"
DEFINE_LOG_CATEGORY(LogGameCommonModule);

void FGameCommonModule::StartupModule()
{
	UE_LOG(LogGameCommonModule, Display, TEXT("GameCommon Module Startup, Maintainer: %s"), *Author);
}

void FGameCommonModule::ShutdownModule()
{
	UE_LOG(LogGameCommonModule, Display, TEXT("GameCommon Module Shutdown, Have a nice day"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameCommonModule, GameCommonModule)

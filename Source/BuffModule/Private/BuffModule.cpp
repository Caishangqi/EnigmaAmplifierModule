#include "BuffModule.h"

#define LOCTEXT_NAMESPACE "FBuffModule"
DEFINE_LOG_CATEGORY(LogBuffModule);

void FBuffModule::StartupModule()
{
	UE_LOG(LogBuffModule, Display, TEXT("Game Buff Module Startup, Maintainer: %s"), *Author);
}

void FBuffModule::ShutdownModule()
{
	UE_LOG(LogBuffModule, Display, TEXT("Game Buff Module Shutdown, Have a nice day"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBuffModule, BuffModule)

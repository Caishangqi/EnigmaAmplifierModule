#include "CoreAttributeModule.h"

#define LOCTEXT_NAMESPACE "FCoreAttributeModule"
DEFINE_LOG_CATEGORY(LogCoreAttributeModule);

void FCoreAttributeModule::StartupModule()
{
	UE_LOG(LogCoreAttributeModule, Display, TEXT("CoreAttribute Module Startup, Maintainer: %s"), *Author);
}

void FCoreAttributeModule::ShutdownModule()
{
	UE_LOG(LogCoreAttributeModule, Display, TEXT("CoreAttribute Module Shutdown, Have a nice day"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCoreAttributeModule, CoreAttributeModule)

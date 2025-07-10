using UnrealBuildTool;

public class BuffModule : ModuleRules
{
	public BuffModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "UMG", "GameCommonModule"
			}
		);
		PublicIncludePathModuleNames.AddRange(new string[]
		{
			// "IG2_TPDelivery"
		});
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GameCommonModule"
			}
		);
	}
}
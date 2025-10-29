// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BSc2A_Ritual : ModuleRules
{
	public BSc2A_Ritual(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BSc2A_Ritual",
			"BSc2A_Ritual/Variant_Horror",
			"BSc2A_Ritual/Variant_Horror/UI",
			"BSc2A_Ritual/Variant_Shooter",
			"BSc2A_Ritual/Variant_Shooter/AI",
			"BSc2A_Ritual/Variant_Shooter/UI",
			"BSc2A_Ritual/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

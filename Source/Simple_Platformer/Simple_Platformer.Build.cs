// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Simple_Platformer : ModuleRules
{
	public Simple_Platformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootingSystem : ModuleRules
{
	public ShootingSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "PhysicsCore" });
	}
}

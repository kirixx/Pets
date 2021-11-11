// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TicTacToe : ModuleRules
{
	public TicTacToe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"TicTacToe"
     }
     );

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

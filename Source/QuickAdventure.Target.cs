// Copyright Dawid Harendarz.

using UnrealBuildTool;
using System.Collections.Generic;

public class QuickAdventureTarget : TargetRules
{
	public QuickAdventureTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "QuickAdventure" } );
	}
}

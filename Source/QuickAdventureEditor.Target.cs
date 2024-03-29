// Copyright Dawid Harendarz.

using UnrealBuildTool;
using System.Collections.Generic;

public class QuickAdventureEditorTarget : TargetRules
{
	public QuickAdventureEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "QuickAdventure" } );
	}
}

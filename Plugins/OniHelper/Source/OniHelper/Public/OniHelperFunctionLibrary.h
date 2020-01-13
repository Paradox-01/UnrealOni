// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OniHelperFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class ONIHELPER_API UOniHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintPure, Category = "System Information")
		static FText GetProjectVersion()
		{
			FString ProjectVersion;
			
			GConfig->GetString(
				TEXT("/Script/EngineSettings.GeneralProjectSettings"),
				TEXT("ProjectVersion"),
				ProjectVersion,
				GGameIni);

			return FText::FromString(ProjectVersion);
		}

		UFUNCTION(BlueprintCallable, Category = "System Information")
		static void SetProjectVersion(FString ProjectVersion)
		{
			GConfig->SetString(
				TEXT("/Script/EngineSettings.GeneralProjectSettings"),
				TEXT("ProjectVersion"),
				ProjectVersion.GetCharArray().GetData(),
				GGameIni);

			GConfig->Flush(false, GGameIni);
		}

		//
		UFUNCTION(BlueprintPure, Category = "OniHelper")
		static float GetDisplayGamma()
		{
			float Gamma;
			GConfig->GetFloat(
				TEXT("/Script/Engine.Engine"),
				TEXT("DisplayGamma"),
				Gamma,
				GEngineIni);

			return Gamma;
		}

		UFUNCTION(BlueprintCallable, Category = "OniHelper")
		static void SetDisplayGamma(float Gamma)
		{
			GConfig->SetFloat(
				TEXT("/Script/Engine.Engine"),
				TEXT("DisplayGamma"),
				Gamma,
				GEngineIni);

			GConfig->Flush(false, GEngineIni);
		}

		//
		UFUNCTION(BlueprintPure, Category = "OniHelper")
		static bool GetWindowBorder()
		{
			FString BorderlessWindow;
			bool returnBool;
			
			GConfig->GetString(
				TEXT("/Script/EngineSettings.GeneralProjectSettings"),
				TEXT("bUseBorderlessWindow"),
				BorderlessWindow,
				GGameIni);

			if (BorderlessWindow == "True")
				returnBool = true;
			else
				returnBool = false;

			return returnBool;
		}

		UFUNCTION(BlueprintCallable, Category = "OniHelper")
		static void SetWindowBorder(bool Borderless)
		{
			if (Borderless)
				GConfig->SetString(
					TEXT("/Script/EngineSettings.GeneralProjectSettings"),
					TEXT("bUseBorderlessWindow"),
					TEXT("True"),
					GGameIni);
			else
				GConfig->SetString(
					TEXT("/Script/EngineSettings.GeneralProjectSettings"),
					TEXT("bUseBorderlessWindow"),
					TEXT("False"),
					GGameIni);

			GConfig->Flush(false, GGameIni);
		}
};
// Fill out your copyright notice in the Description page of Project Settings.

#include "EXCCameraModifier.h"
#include "EXCPlayerCameraManager.h"

bool UEXCCameraModifier::ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV)
{
	bool bShouldStop = Super::ModifyCamera(DeltaTime, InOutPOV);

	if (bShouldStop)
		return true;

	if (AEXCPlayerCameraManager* EXCManager = Cast<AEXCPlayerCameraManager>(CameraOwner))
	{
		FExtraViewInfo& InOutPOVExtraInfo = EXCManager->ViewTargetExtraInfo;

		bool bShouldStopExtra = ModifyCameraWithExtra(DeltaTime, InOutPOV, InOutPOVExtraInfo);

		if (bShouldStopExtra)
			return true;
	}

	return false;
}

bool UEXCCameraModifier::ModifyCameraWithExtra(float DeltaTime, FMinimalViewInfo& InOutPOV, FExtraViewInfo& InOutExtraPOV)
{
	BlueprintModifyCameraWithExtra(DeltaTime, InOutPOV.Location, InOutPOV.Rotation, InOutPOV.FOV, InOutExtraPOV, InOutPOV.Location, InOutPOV.Rotation, InOutPOV.FOV, InOutExtraPOV);

	return false;
}

void UEXCCameraModifier::Combine(FExtraViewInfo InExtraViewInfo, FExtraViewInfo InModifierExtraViewInfo, FExtraViewInfo& OutExtraViewInfo, float GlobalAlpha)
{
	OutExtraViewInfo = InExtraViewInfo;

	if (!InModifierExtraViewInfo.IsAdditiveZero())
	{
		OutExtraViewInfo.AdditiveSocketOffset += (InModifierExtraViewInfo.AdditiveSocketOffset) * GlobalAlpha;
		OutExtraViewInfo.AdditiveTargetOffset += (InModifierExtraViewInfo.AdditiveTargetOffset) * GlobalAlpha;
		OutExtraViewInfo.AdditiveSpringArmLength += (InModifierExtraViewInfo.AdditiveSpringArmLength) * GlobalAlpha;
	}

	if (!InModifierExtraViewInfo.IsBaseZero() && InExtraViewInfo.GreaterPriorityApplied < Priority)
	{
		OutExtraViewInfo.GreaterPriorityApplied = Priority;

		OutExtraViewInfo.BaseDeltaSocketOffset = (InModifierExtraViewInfo.BaseSocketOffset - InExtraViewInfo.DefaultSocketOffset) * GlobalAlpha;
		OutExtraViewInfo.BaseDeltaTargetOffset = (InModifierExtraViewInfo.BaseTargetOffset - InExtraViewInfo.DefaultTargetOffset) * GlobalAlpha;
		OutExtraViewInfo.BaseDeltaSpringArmLenght = (InModifierExtraViewInfo.BaseSpringArmLength - InExtraViewInfo.DefaultSpringArmLenght) * GlobalAlpha;
	}
}

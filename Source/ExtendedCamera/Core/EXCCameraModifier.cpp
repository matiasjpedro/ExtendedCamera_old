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

//TODO: This could be in the static library blueprint
void UEXCCameraModifier::Combine(FExtraViewInfo InExtraViewInfo, FExtraViewInfo InModifierExtraViewInfo, FExtraViewInfo& OutExtraViewInfo, float GlobalAlpha)
{
	OutExtraViewInfo = InExtraViewInfo;

	if (!InModifierExtraViewInfo.IsAdditiveZero())
	{
		OutExtraViewInfo.SocketOffset.AdditiveValue += (InModifierExtraViewInfo.SocketOffset.AdditiveValue) * GlobalAlpha;
		OutExtraViewInfo.TargetOffset.AdditiveValue += (InModifierExtraViewInfo.TargetOffset.AdditiveValue) * GlobalAlpha;
		OutExtraViewInfo.ArmLenght.AdditiveValue += (InModifierExtraViewInfo.ArmLenght.AdditiveValue) * GlobalAlpha;
	}

	if (!InModifierExtraViewInfo.IsBaseZero() && InExtraViewInfo.GreaterPriorityApplied < Priority)
	{
		OutExtraViewInfo.GreaterPriorityApplied = Priority;

		OutExtraViewInfo.SocketOffset.BaseDeltaValue = (InModifierExtraViewInfo.SocketOffset.BaseValue - InExtraViewInfo.SocketOffset.GetDefaultBaseValue()) * GlobalAlpha;
		OutExtraViewInfo.TargetOffset.BaseDeltaValue = (InModifierExtraViewInfo.TargetOffset.BaseValue - InExtraViewInfo.TargetOffset.GetDefaultBaseValue()) * GlobalAlpha;
		OutExtraViewInfo.ArmLenght.BaseDeltaValue = (InModifierExtraViewInfo.ArmLenght.BaseValue - InExtraViewInfo.ArmLenght.GetDefaultBaseValue()) * GlobalAlpha;
	}
}

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
		bool bShouldStopExtra = ModifyCameraWithExtra(DeltaTime, InOutPOV, EXCManager->GetViewTargetExtraInfo());

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
void UEXCCameraModifier::Combine(const FExtraViewInfo& InExtraViewInfo, const FExtraViewInfo& InModifierExtraViewInfo, FExtraViewInfo& OutExtraViewInfo, float GlobalAlpha)
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

		if (InExtraViewInfo.IsBaseZero())
		{
			const FEXCVector& CurrentSocketOffset = InExtraViewInfo.SocketOffset;
			const FEXCVector& CurrentTargetOffset = InExtraViewInfo.TargetOffset;
			const FEXCFloat& CurrentArmLenght = InExtraViewInfo.ArmLenght;

			OutExtraViewInfo.SocketOffset.BaseDeltaValue = (InModifierExtraViewInfo.SocketOffset.BaseValue - CurrentSocketOffset.GetDefaultBaseValue()) * GlobalAlpha;
			OutExtraViewInfo.TargetOffset.BaseDeltaValue = (InModifierExtraViewInfo.TargetOffset.BaseValue - CurrentTargetOffset.GetDefaultBaseValue()) * GlobalAlpha;
			OutExtraViewInfo.ArmLenght.BaseDeltaValue = (InModifierExtraViewInfo.ArmLenght.BaseValue - CurrentArmLenght.GetDefaultBaseValue()) * GlobalAlpha;

			OutExtraViewInfo.SocketOffset.BaseValue = CurrentSocketOffset.GetDefaultBaseValue() + OutExtraViewInfo.SocketOffset.BaseDeltaValue;
			OutExtraViewInfo.TargetOffset.BaseValue = CurrentTargetOffset.GetDefaultBaseValue() + OutExtraViewInfo.TargetOffset.BaseDeltaValue;
			OutExtraViewInfo.ArmLenght.BaseValue = CurrentArmLenght.GetDefaultBaseValue() + OutExtraViewInfo.ArmLenght.BaseDeltaValue;
		}
		else
		{
			OutExtraViewInfo.SocketOffset.BaseValue = FMath::Lerp(InExtraViewInfo.SocketOffset.BaseValue, InModifierExtraViewInfo.SocketOffset.BaseValue, GlobalAlpha);
			OutExtraViewInfo.TargetOffset.BaseValue = FMath::Lerp(InExtraViewInfo.TargetOffset.BaseValue, InModifierExtraViewInfo.TargetOffset.BaseValue, GlobalAlpha);
			OutExtraViewInfo.ArmLenght.BaseValue = FMath::Lerp(InExtraViewInfo.ArmLenght.BaseValue, InModifierExtraViewInfo.ArmLenght.BaseValue, GlobalAlpha);
		}
	}
}

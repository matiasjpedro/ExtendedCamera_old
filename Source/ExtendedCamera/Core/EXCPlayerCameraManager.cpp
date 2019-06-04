// Fill out your copyright notice in the Description page of Project Settings.


#include "EXCPlayerCameraManager.h"
#include "EXCSpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "EXCCameraModifier.h"

UCameraModifier* AEXCPlayerCameraManager::AddNewCameraModifier(TSubclassOf<class UCameraModifier> ModifierClass)
{
	UCameraModifier* CameraModifier = Super::AddNewCameraModifier(ModifierClass);

	if (UEXCCameraModifier* EXCCameraModifier = Cast<UEXCCameraModifier>(CameraModifier))
	{
		if(EXCCameraModifier->bStartDisabled)
			EXCCameraModifier->DisableModifier(true);
	}

	return CameraModifier;
}

void AEXCPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	ViewTargetExtraInfo = FExtraViewInfo();

	APawn* TargetPawn = OutVT.GetTargetPawn();

	if (TargetPawn != nullptr)
	{
		UEXCSpringArmComponent* EXCSpringArm = TargetPawn->FindComponentByClass<UEXCSpringArmComponent>();
		
		if (EXCSpringArm != nullptr)
		{
			ViewTargetExtraInfo.SocketOffset = FEXCVector(EXCSpringArm->DefaultSocketOffset);
			ViewTargetExtraInfo.TargetOffset = FEXCVector(EXCSpringArm->DefaultTargetOffset);
			ViewTargetExtraInfo.ArmLenght = FEXCFloat(EXCSpringArm->DefaultSpringArmLenght);
		}
	}

	Super::UpdateViewTarget(OutVT, DeltaTime);

	if (TargetPawn != nullptr)
	{
		UEXCSpringArmComponent* EXCSpringArm = TargetPawn->FindComponentByClass<UEXCSpringArmComponent>();

		if (EXCSpringArm != nullptr)
		{
			if (!ViewTargetExtraInfo.IsAdditiveZero())
			{
				EXCSpringArm->AdditiveSpringArmLenght = ViewTargetExtraInfo.ArmLenght.AdditiveValue;
				EXCSpringArm->AdditiveSocketOffset = ViewTargetExtraInfo.SocketOffset.AdditiveValue;
				EXCSpringArm->AdditiveTargetOffset = ViewTargetExtraInfo.TargetOffset.AdditiveValue;

				if (!EXCSpringArm->bIsAdditiveDirty)
					EXCSpringArm->bIsAdditiveDirty = true;
			}
			else if(EXCSpringArm->bIsAdditiveDirty)
			{
				EXCSpringArm->CleanAdditive();
			}
			
			if (!ViewTargetExtraInfo.IsBaseZero())
			{
				EXCSpringArm->BaseSpringArmLenght = ViewTargetExtraInfo.ArmLenght.BaseValue;
				EXCSpringArm->BaseSocketOffset = ViewTargetExtraInfo.SocketOffset.BaseValue;
				EXCSpringArm->BaseTargetOffset = ViewTargetExtraInfo.TargetOffset.BaseValue;

				if (!EXCSpringArm->bIsBaseDirty)
					EXCSpringArm->bIsBaseDirty = true;
			}
			else if(EXCSpringArm->bIsBaseDirty)
			{
				EXCSpringArm->CleanBase();
			}

			/*UE_LOG(LogTemp, Log, TEXT("SocketOffset %s"), *ViewTargetExtraInfo.AdditiveSocketOffset.ToString());
			UE_LOG(LogTemp, Log, TEXT("TargetOffset %s"), *ViewTargetExtraInfo.AdditiveTargetOffset.ToString());
			UE_LOG(LogTemp, Log, TEXT("SpringArmLenght %f"), ViewTargetExtraInfo.AdditiveSpringArmLength);*/
		}
	}
}

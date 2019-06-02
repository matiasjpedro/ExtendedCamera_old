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
			ViewTargetExtraInfo.DefaultSocketOffset = EXCSpringArm->DefaultSocketOffset;
			ViewTargetExtraInfo.DefaultTargetOffset = EXCSpringArm->DefaultTargetOffset;
			ViewTargetExtraInfo.DefaultSpringArmLenght = EXCSpringArm->DefaultSpringArmLenght;
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
				EXCSpringArm->AdditiveSpringArmLenght = ViewTargetExtraInfo.AdditiveSpringArmLength;
				EXCSpringArm->AdditiveSocketOffset = ViewTargetExtraInfo.AdditiveSocketOffset;
				EXCSpringArm->AdditiveTargetOffset = ViewTargetExtraInfo.AdditiveTargetOffset;

				if (!EXCSpringArm->bIsAdditiveModified)
					EXCSpringArm->bIsAdditiveModified = true;
			}
			else if(EXCSpringArm->bIsAdditiveModified)
			{
				EXCSpringArm->RestartAdditive();
			}
			
			if (!ViewTargetExtraInfo.IsBaseDeltaZero())
			{
				EXCSpringArm->BaseSpringArmLenght = ViewTargetExtraInfo.DefaultSpringArmLenght + ViewTargetExtraInfo.BaseDeltaSpringArmLenght;
				EXCSpringArm->BaseSocketOffset = ViewTargetExtraInfo.DefaultSocketOffset + ViewTargetExtraInfo.BaseDeltaSocketOffset;
				EXCSpringArm->BaseTargetOffset = ViewTargetExtraInfo.DefaultTargetOffset + ViewTargetExtraInfo.BaseDeltaTargetOffset;

				if (!EXCSpringArm->bIsBaseModified)
					EXCSpringArm->bIsBaseModified = true;
			}
			else if(!EXCSpringArm->bIsBaseModified)
			{
				EXCSpringArm->RestartBase();
			}

			UE_LOG(LogTemp, Log, TEXT("SocketOffset %s"), *ViewTargetExtraInfo.AdditiveSocketOffset.ToString());
			UE_LOG(LogTemp, Log, TEXT("TargetOffset %s"), *ViewTargetExtraInfo.AdditiveTargetOffset.ToString());
			UE_LOG(LogTemp, Log, TEXT("SpringArmLenght %f"), ViewTargetExtraInfo.AdditiveSpringArmLength);
		}
	}
}

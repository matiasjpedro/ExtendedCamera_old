// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EXCTypes.h"
#include "Camera/PlayerCameraManager.h"
#include "EXCPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDCAMERA_API AEXCPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()


public:

	/** Current ViewTarget */
	UPROPERTY(transient)
	struct FExtraViewInfo ViewTargetExtraInfo;

	struct FExtraViewInfo& GetViewTargetExtraInfo() { return ViewTargetExtraInfo; }

	/** Pending view target for blending */
	UPROPERTY(transient)
	struct FExtraViewInfo PendingViewTargetExtraInfo;

	/** 
	 * Creates and initializes a new camera modifier of the specified class. 
	 * @param ModifierClass - The class of camera modifier to create.
	 * @return Returns the newly created camera modifier.
	 */
	virtual class UCameraModifier* AddNewCameraModifier(TSubclassOf<class UCameraModifier> ModifierClass) override;
	
protected:

	/**
	 * Calculates an updated POV for the given viewtarget.
	 * @param	OutVT		ViewTarget to update.
	 * @param	DeltaTime	Delta Time since last camera update (in seconds).
	 */

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};

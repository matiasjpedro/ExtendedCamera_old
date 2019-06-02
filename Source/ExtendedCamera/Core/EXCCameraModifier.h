// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EXCTypes.h"
#include "Camera/CameraModifier.h"
#include "EXCCameraModifier.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDCAMERA_API UEXCCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:

	/** If true, no other modifiers of same priority allowed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CameraModifier)
	uint32 bStartDisabled : 1;

	/**
	 * Directly modifies variables in the owning camera
	 * @param	DeltaTime	Change in time since last update
	 * @param	InOutPOV	Current Point of View, to be updated.
	 * @return	bool		True if should STOP looping the chain, false otherwise
	 */
	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;
	
	/**
	 * Directly modifies variables in the owning camera
	 * @param	DeltaTime	Change in time since last update
	 * @param	InOutPOV	Current Point of View, to be updated.
	 * @param	InOutExtraPOV Extra data of the Point of View, to be updated.
	 * @return	bool		True if should STOP looping the chain, false otherwise
	 */
	virtual bool ModifyCameraWithExtra(float DeltaTime, struct FMinimalViewInfo& InOutPOV, struct FExtraViewInfo& InOutExtraPOV);

	/** 
	 * Called per tick that the modifier is active to allow Blueprinted modifiers to modify the camera's transform. 
	 * Scaling by Alpha happens after this in code, so no need to deal with that in the blueprint.
	 * @param	DeltaTime	Change in time since last update
	 * @param	ViewLocation		The current camera location.
	 * @param	ViewRotation		The current camera rotation.
	 * @param	FOV					The current camera fov.
	 * @param	NewViewLocation		(out) The modified camera location.
	 * @param	NewViewRotation		(out) The modified camera rotation.
	 * @param	NewFOV				(out) The modified camera FOV.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BlueprintModifyCameraWithExtra(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FExtraViewInfo ViewExtraInfo, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV, FExtraViewInfo& NewViewExtraInfo);
	

protected:

	UFUNCTION(BlueprintCallable)
	void Combine(FExtraViewInfo InExtraViewInfo, FExtraViewInfo InModifierExtraViewInfo, FExtraViewInfo& OutExtraViewInfo, float GlobalAlpha  = 1.f);
};

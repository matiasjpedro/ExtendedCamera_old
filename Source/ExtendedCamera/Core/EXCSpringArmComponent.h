// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "EXCSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDCAMERA_API UEXCSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	

public:

	/** Value to add to the target arm length, e.g. caused by camera modifiers. */
	float AdditiveSpringArmLenght;
	float BaseSpringArmLenght;
	float DefaultSpringArmLenght;

	/** Value to add to the target arm length, e.g. caused by camera modifiers. */
	FVector AdditiveSocketOffset;
	FVector BaseSocketOffset;
	FVector DefaultSocketOffset;

	/** Value to add to the target arm length, e.g. caused by camera modifiers. */
	FVector AdditiveTargetOffset;
	FVector BaseTargetOffset;
	FVector DefaultTargetOffset;

	/**
	 * BeginsPlay for the component.  Occurs at level startup or actor spawn. This is before BeginPlay (Actor or Component).
	 * All Components (that want initialization) in the level will be Initialized on load before any
	 * Actor/Component gets BeginPlay.
	 * Requires component to be registered and initialized.
	 */
	virtual void BeginPlay() override;

	bool bIsAdditiveModified = false;
	void RestartAdditive();

	bool bIsBaseModified = false;
	void RestartBase();

protected:

	bool bInitialized = false;

	virtual void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag,
		float DeltaTime) override;
};

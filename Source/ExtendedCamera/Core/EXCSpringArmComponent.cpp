// Fill out your copyright notice in the Description page of Project Settings.


#include "EXCSpringArmComponent.h"

void UEXCSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultSpringArmLenght = TargetArmLength;
	BaseSpringArmLenght = TargetArmLength;

	DefaultSocketOffset = SocketOffset;
	BaseSocketOffset = SocketOffset;

	DefaultTargetOffset = TargetOffset;
	BaseTargetOffset = TargetOffset;

	bInitialized = true;
}

void UEXCSpringArmComponent::CleanAdditive()
{
	bIsAdditiveDirty = false;

	AdditiveSpringArmLenght = 0;
	AdditiveSocketOffset = FVector::ZeroVector;
	AdditiveTargetOffset = FVector::ZeroVector;
}

void UEXCSpringArmComponent::CleanBase()
{
	bIsBaseDirty = false;

	BaseSpringArmLenght = DefaultSpringArmLenght;
	BaseSocketOffset = DefaultSocketOffset;
	BaseTargetOffset = DefaultTargetOffset;
}

void UEXCSpringArmComponent::UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag,
	float DeltaTime)
{
	if (bInitialized)
	{
		TargetArmLength = BaseSpringArmLenght + AdditiveSpringArmLenght;
		SocketOffset = BaseSocketOffset + AdditiveSocketOffset;
		TargetOffset = BaseTargetOffset + AdditiveTargetOffset;
	}

	Super::UpdateDesiredArmLocation(bDoTrace, bDoLocationLag, bDoRotationLag, DeltaTime);
}
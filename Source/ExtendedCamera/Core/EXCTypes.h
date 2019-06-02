#pragma once

#include "CoreMinimal.h"
#include "EXCTypes.generated.h"

USTRUCT(BlueprintType)
struct FExtraViewInfo
{
	GENERATED_USTRUCT_BODY()

	uint8 GreaterPriorityApplied = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector AdditiveSocketOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector AdditiveTargetOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float AdditiveSpringArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector BaseSocketOffset;
	FVector BaseDeltaSocketOffset;
	FVector DefaultSocketOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector BaseTargetOffset;
	FVector BaseDeltaTargetOffset;
	FVector DefaultTargetOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseSpringArmLength;
	float BaseDeltaSpringArmLenght;
	float DefaultSpringArmLenght;

	// Is this equivalent to the other one?
	bool Equals(const FExtraViewInfo& OtherInfo) const;

	/** Whether this property set modifies the camera at all. */
	bool IsZero() const;

	bool IsAdditiveZero() const;

	bool IsBaseZero() const;

	bool IsBaseDeltaZero() const;
};

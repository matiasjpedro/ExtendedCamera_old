#pragma once

#include "CoreMinimal.h"
#include "EXCTypes.generated.h"

USTRUCT(BlueprintType)
struct FEXCFloat
{
	GENERATED_USTRUCT_BODY()

	FEXCFloat() :
		AdditiveValue(0.f),
		BaseValue(0.f),
		BaseDeltaValue(0.f),
		DefaultBaseValue(0.f)
	{
	}

	FEXCFloat(const float& InDefaultBaseValue) :
		AdditiveValue(0.f),
		BaseValue(0.f),
		BaseDeltaValue(0.f),
		DefaultBaseValue(InDefaultBaseValue)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AdditiveValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseValue;
	float BaseDeltaValue;

	bool Equals(const FEXCFloat& OtherEXCVector) const;
	bool IsZero() const;

	const float& GetDefaultBaseValue() const;

private:

	float DefaultBaseValue;
};

USTRUCT(BlueprintType)
struct FEXCVector
{
	GENERATED_USTRUCT_BODY()

	FEXCVector() :
		AdditiveValue(FVector::ZeroVector),
		BaseValue(FVector::ZeroVector),
		BaseDeltaValue(FVector::ZeroVector),
		DefaultBaseValue(FVector::ZeroVector)
	{
	}

	FEXCVector(const FVector& InDefaultBaseValue) :
		AdditiveValue(FVector::ZeroVector),
		BaseValue(FVector::ZeroVector),
		BaseDeltaValue(FVector::ZeroVector),
		DefaultBaseValue(InDefaultBaseValue)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector AdditiveValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector BaseValue;
	FVector BaseDeltaValue;

	bool Equals(const FEXCVector& OtherEXCVector) const;
	bool IsZero() const;

	const FVector& GetDefaultBaseValue() const;

private:

	FVector DefaultBaseValue;
};

USTRUCT(BlueprintType)
struct FExtraViewInfo
{
	GENERATED_USTRUCT_BODY()

	//TODO: Maybe the priority could be in the specifics ones?
	uint8 GreaterPriorityApplied = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=SpringArm)
	FEXCVector SocketOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=SpringArm)
	FEXCVector TargetOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=SpringArm)
	FEXCFloat ArmLenght;

	// Is this equivalent to the other one?
	bool Equals(const FExtraViewInfo& OtherInfo) const;

	/** Whether this property set modifies the camera at all. */
	bool IsZero() const;

	bool IsAdditiveZero() const;
	bool IsBaseZero() const;
	bool IsBaseDeltaZero() const;
};

#include "EXCTypes.h"

bool FExtraViewInfo::Equals(const FExtraViewInfo& OtherInfo) const
{
	FExtraViewInfo Delta;

	Delta.AdditiveSpringArmLength = AdditiveSpringArmLength - OtherInfo.AdditiveSpringArmLength;
	Delta.AdditiveSocketOffset = AdditiveSocketOffset - OtherInfo.AdditiveSocketOffset;
	Delta.AdditiveTargetOffset = AdditiveTargetOffset - OtherInfo.AdditiveTargetOffset;

	Delta.BaseSpringArmLength = BaseSpringArmLength - OtherInfo.BaseSpringArmLength;
	Delta.BaseSocketOffset = BaseSocketOffset - OtherInfo.BaseSocketOffset;
	Delta.BaseTargetOffset = BaseTargetOffset - OtherInfo.BaseTargetOffset;

	return Delta.IsZero();
}

bool FExtraViewInfo::IsZero() const
{
	return IsAdditiveZero() && IsBaseZero();
}

bool FExtraViewInfo::IsAdditiveZero() const
{
	return AdditiveSocketOffset.IsZero() && AdditiveTargetOffset.IsZero() && FMath::Abs(AdditiveSpringArmLength) < SMALL_NUMBER;
}

bool FExtraViewInfo::IsBaseZero() const
{
	return BaseSocketOffset.IsZero() && BaseTargetOffset.IsZero() && FMath::Abs(BaseSpringArmLength) < SMALL_NUMBER;
}

bool FExtraViewInfo::IsBaseDeltaZero() const
{
	return BaseDeltaSocketOffset.IsZero() && BaseDeltaTargetOffset.IsZero() && FMath::Abs(BaseDeltaSpringArmLenght) < SMALL_NUMBER;
}


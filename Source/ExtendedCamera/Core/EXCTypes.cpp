#include "EXCTypes.h"

bool FExtraViewInfo::Equals(const FExtraViewInfo& OtherInfo) const
{
	return SocketOffset.Equals(OtherInfo.SocketOffset) && TargetOffset.Equals(OtherInfo.TargetOffset) && ArmLenght.Equals(OtherInfo.ArmLenght);
}

bool FExtraViewInfo::IsZero() const
{
	return IsAdditiveZero() && IsBaseZero();
}

bool FExtraViewInfo::IsAdditiveZero() const
{
	return SocketOffset.AdditiveValue.IsZero() && TargetOffset.AdditiveValue.IsZero() && ArmLenght.AdditiveValue == 0.f;
}

bool FExtraViewInfo::IsBaseZero() const
{
	return SocketOffset.BaseValue.IsZero() && TargetOffset.BaseValue.IsZero() && ArmLenght.BaseValue == 0.f;
}

bool FExtraViewInfo::IsBaseDeltaZero() const
{
	return SocketOffset.BaseDeltaValue.IsZero() && TargetOffset.BaseDeltaValue.IsZero() && FMath::Abs(ArmLenght.BaseDeltaValue) < SMALL_NUMBER;
}

bool FEXCVector::Equals(const FEXCVector& OtherEXCVector) const
{
	FEXCVector Delta;

	Delta.AdditiveValue = AdditiveValue - OtherEXCVector.AdditiveValue;
	Delta.BaseValue = BaseValue - OtherEXCVector.BaseValue;

	return Delta.IsZero();
}

bool FEXCVector::IsZero() const
{
	return AdditiveValue.IsZero() && BaseValue.IsZero() && BaseDeltaValue.IsZero();
}

const FVector& FEXCVector::GetDefaultBaseValue() const
{
	return DefaultBaseValue;
}

bool FEXCFloat::Equals(const FEXCFloat& OtherEXCVector) const
{
	FEXCFloat Delta;

	Delta.AdditiveValue = AdditiveValue - OtherEXCVector.AdditiveValue;
	Delta.BaseValue = BaseValue - OtherEXCVector.BaseValue;

	return Delta.IsZero();
}

bool FEXCFloat::IsZero() const
{
	return AdditiveValue == 0.f && BaseValue == 0.f && FMath::Abs(BaseDeltaValue) < SMALL_NUMBER;
}

const float& FEXCFloat::GetDefaultBaseValue() const
{
	return DefaultBaseValue;
}

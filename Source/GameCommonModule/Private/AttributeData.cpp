#include "AttributeData.h"

FAttributeData FAttributeData::operator+(const FAttributeData& Other) const
{
	FAttributeData Result;
	Result.Source                 = Other.Source;
	Result.Health                 = Health + Other.Health;
	Result.ResistPhysic           = ResistPhysic + Other.ResistPhysic;
	Result.DamageReductionPhysic  = DamageReductionPhysic + Other.DamageReductionPhysic;
	Result.ResistMagic            = ResistMagic + Other.ResistMagic;
	Result.DamageReductionMagical = DamageReductionMagical + Other.DamageReductionMagical;

	//Result.bIsDead = bIsDead || Other.bIsDead;
	return Result;
}

FAttributeData FAttributeData::operator-(const FAttributeData& Other) const
{
	FAttributeData Result;
	Result.Source                 = Other.Source;
	Result.Health                 = Health - Other.Health;
	Result.ResistPhysic           = ResistPhysic - Other.ResistPhysic;
	Result.DamageReductionPhysic  = DamageReductionPhysic - Other.DamageReductionPhysic;
	Result.ResistMagic            = ResistMagic - Other.ResistMagic;
	Result.DamageReductionMagical = DamageReductionMagical - Other.DamageReductionMagical;

	//Result.bIsDead = bIsDead;
	return Result;
}

FAttributeData& FAttributeData::operator+=(const FAttributeData& Other)
{
	Source = Other.Source;
	Health += Other.Health;
	ResistPhysic += Other.ResistPhysic;
	DamageReductionPhysic += Other.DamageReductionPhysic;
	ResistMagic += Other.ResistMagic;
	DamageReductionMagical += Other.DamageReductionMagical;
	//bIsDead = bIsDead || Other.bIsDead;
	return *this;
}

FAttributeData& FAttributeData::operator-=(const FAttributeData& Other)
{
	Source = Other.Source;
	Health -= Other.Health;
	ResistPhysic -= Other.ResistPhysic;
	DamageReductionPhysic -= Other.DamageReductionPhysic;
	ResistMagic -= Other.ResistMagic;
	DamageReductionMagical -= Other.DamageReductionMagical;
	return *this;
}

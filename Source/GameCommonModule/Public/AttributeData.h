#pragma once

#include "CoreMinimal.h"
#include "AttributeData.generated.h"
/// General RPG Character Attributes
USTRUCT(Blueprintable)
struct FAttributeData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true", ToolTip = "The Damage Soruce from"))
	TObjectPtr<UObject> Source = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attributes, meta = (AllowPrivateAccess = "true", ToolTip = "Owner's Health"))
	float Health = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attributes, meta = (AllowPrivateAccess = "true", ToolTip = "Owner's Armor"))
	float ResistPhysic = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attributes, meta = (AllowPrivateAccess = "true", ToolTip = "Owner's Physic Damage Reduction"))
	float DamageReductionPhysic = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attributes, meta = (AllowPrivateAccess = "true", ToolTip = "Owner's MagicResist"))
	float ResistMagic = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attributes, meta = (AllowPrivateAccess = "true", ToolTip = "Owner's Magical Damage Reduction"))
	float DamageReductionMagical = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attributes, meta = (AllowPrivateAccess = "true", ToolTip = "Whether or not owner is dead"))
	bool bIsDead = false;

public:
	FAttributeData  operator+(const FAttributeData& Other) const;
	FAttributeData  operator-(const FAttributeData& Other) const;
	FAttributeData& operator+=(const FAttributeData& Other);
	FAttributeData& operator-=(const FAttributeData& Other);
};

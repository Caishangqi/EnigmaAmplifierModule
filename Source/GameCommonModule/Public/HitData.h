#pragma once
#include "CoreMinimal.h"
#include "HitData.generated.h"

/**
 * A struct to represent hit-related data including damage and healing attributes.
 */
USTRUCT(Blueprintable)
struct FHitData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true", ToolTip = "The Damage Soruce from"))
	TObjectPtr<UObject> Source = nullptr;

	/// List Of Attributes (Simple Version)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true", ToolTip = "Delta True Damage Deal"))
	float DamageTrue = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true", ToolTip = "Delta Physics Damage Deal"))
	float DamagePhysic = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true", ToolTip = "Delta Heal Damage Deal"))
	float DirectHeal = 0; // Negative value means direct damage (different from true damage)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true", ToolTip = "Delta Heal Damage Deal"))
	bool IsValidHit = true; // False means that the hit is invalid, should not be processed.
};

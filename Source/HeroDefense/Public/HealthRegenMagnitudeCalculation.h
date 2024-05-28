// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HealthRegenMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class HERODEFENSE_API UHealthRegenMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	UHealthRegenMagnitudeCalculation();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	//Its like copy of Health Attribute 
	FGameplayEffectAttributeCaptureDefinition HealthDef;
	FGameplayEffectAttributeCaptureDefinition MaxHealthDef;
	
};

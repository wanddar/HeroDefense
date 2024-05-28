// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MyGameplayMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class HERODEFENSE_API UMyGameplayMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	UMyGameplayMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition StaminaDef;
	FGameplayEffectAttributeCaptureDefinition MaxStaminaDef;
	;
};

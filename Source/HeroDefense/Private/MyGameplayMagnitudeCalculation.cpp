// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayMagnitudeCalculation.h"

#include "Attributes/MyAttributeSetBase.h"

UMyGameplayMagnitudeCalculation::UMyGameplayMagnitudeCalculation()
{
	
	StaminaDef.AttributeToCapture = UMyAttributeSetBase::GetStaminaAttribute();
	//Who own Attribute we capture(Target or Source)
	StaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	//Freeze Attribute in moment of applying so value cant change(true)
	//Value can change 
	StaminaDef.bSnapshot = false;
	
	MaxStaminaDef.AttributeToCapture = UMyAttributeSetBase::GetMaxStaminaAttribute();
	MaxStaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStaminaDef.bSnapshot = false;

	
	//Add them to array
	RelevantAttributesToCapture.Add(StaminaDef);
	RelevantAttributesToCapture.Add(MaxStaminaDef);
}

float UMyGameplayMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{


	//Collecting Data 
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//Put in Variable attr value 
	float Stamina = 0.0f;
	GetCapturedAttributeMagnitude(StaminaDef,Spec,EvaluationParameters,Stamina);

	float MaxStamina = 0.0f;
	GetCapturedAttributeMagnitude(MaxStaminaDef,Spec,EvaluationParameters,MaxStamina);


	//Logic 
	
	if (Stamina+0.1f>MaxStamina)
	{
		return MaxStamina-Stamina;
	}
	
	return 0.1f;

}
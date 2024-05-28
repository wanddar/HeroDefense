// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthRegenMagnitudeCalculation.h"

#include "Attributes/MyAttributeSetBase.h"

UHealthRegenMagnitudeCalculation::UHealthRegenMagnitudeCalculation()
{
	
    HealthDef.AttributeToCapture = UMyAttributeSetBase::GetHealthAttribute();
    //Who own Attribute we capture(Target or Source)
    HealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    //Freeze Attribute in moment of applying so value cant change(true)
    //Value can change if false
    HealthDef.bSnapshot = false;
	
    MaxHealthDef.AttributeToCapture = UMyAttributeSetBase::GetMaxHealthAttribute();
    MaxHealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    MaxHealthDef.bSnapshot = false;

	
    //Add them to array
    RelevantAttributesToCapture.Add(HealthDef);
    RelevantAttributesToCapture.Add(MaxHealthDef);
}

float UHealthRegenMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{


    //Collecting Data 
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    //Put in Variable attr value 
    float Health = 0.0f;
    GetCapturedAttributeMagnitude(HealthDef,Spec,EvaluationParameters,Health);

    float MaxHealth = 0.0f;
    GetCapturedAttributeMagnitude(MaxHealthDef,Spec,EvaluationParameters,MaxHealth);


    //Logic 
	
    if (Health + 0.5f >MaxHealth)
    {
        return MaxHealth-Health;
    }
	
    return 0.5f;
}
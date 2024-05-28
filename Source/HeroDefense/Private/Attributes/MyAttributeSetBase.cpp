// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/MyAttributeSetBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "MyCharacterBase.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSetBase::UMyAttributeSetBase()
{

}


void UMyAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute==GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.0f,GetMaxStamina());
	}

	if (Attribute==GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.0f,GetMaxHealth());
	}

	if (Attribute==GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.0f,GetMaxMana());
	}
}


bool UMyAttributeSetBase::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	const bool bIsDamage = Data.EvaluatedData.Magnitude<0;
	float Magnitude = Data.EvaluatedData.Magnitude;;
	float FinalMagnitude = Magnitude;
	const FGameplayAttribute AffectedAttr = Data.EvaluatedData.Attribute;
	
	if (AffectedAttr == GetHealthAttribute())
	{
		if (bIsDamage)
		{
			float TargetArmor = Data.Target.GetSet<UMyAttributeSetBase>()->GetArmor();
			
			FinalMagnitude = Magnitude * ((1000-TargetArmor)/1000);

			Data.EvaluatedData.Magnitude = FinalMagnitude;
			return Super::PreGameplayEffectExecute(Data);
		}
		
	}

	if (AffectedAttr == GetStaminaAttribute())
	{
		float TargetStamina = Data.Target.GetSet<UMyAttributeSetBase>()->GetStamina();
		
		if (bIsDamage and TargetStamina+Magnitude<0)
		{
			FinalMagnitude = -TargetStamina;
		}
		if(!bIsDamage and  TargetStamina+Magnitude>GetMaxHealth())
		{
			FinalMagnitude = GetMaxHealth()-TargetStamina;
		}

		Data.EvaluatedData.Magnitude = FinalMagnitude;
		return Super::PreGameplayEffectExecute(Data);
	}
	
	return Super::PreGameplayEffectExecute(Data);
}

void UMyAttributeSetBase::OnRep_Health(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Health,OldValue)
}

void UMyAttributeSetBase::OnRep_MaxHealth(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,MaxHealth,OldValue)
}

void UMyAttributeSetBase::OnRep_Mana(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Mana,OldValue)
}

void UMyAttributeSetBase::OnRep_MaxMana(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,MaxMana,OldValue)
}

void UMyAttributeSetBase::OnRep_Stamina(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Stamina,OldValue)
}

void UMyAttributeSetBase::OnRep_MaxStamina(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,MaxStamina,OldValue)
}

void UMyAttributeSetBase::OnRep_Strength(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Strength,OldValue)
}

void UMyAttributeSetBase::OnRep_Endurance(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Endurance,OldValue)
}

void UMyAttributeSetBase::OnRep_Agility(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Agility,OldValue)
}

void UMyAttributeSetBase::OnRep_Intelligence(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Intelligence,OldValue)
}

void UMyAttributeSetBase::OnRep_Faith(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Faith,OldValue)
}

void UMyAttributeSetBase::OnRep_Heal(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Heal,OldValue)
}

void UMyAttributeSetBase::OnRep_Armor(FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSetBase,Armor,OldValue)
}

void UMyAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	

	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Health,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,MaxHealth,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Mana,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,MaxMana,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Stamina,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,MaxStamina,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Strength,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Endurance,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Agility,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Intelligence,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Faith,COND_None,REPNOTIFY_Always);  
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Heal,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSetBase,Armor,COND_None,REPNOTIFY_Always);
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

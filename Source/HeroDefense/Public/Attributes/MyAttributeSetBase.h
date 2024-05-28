// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MyAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class HERODEFENSE_API UMyAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyAttributeSetBase();
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Attributes")  
	FGameplayAttributeData Health;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Health);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Attributes")  
	FGameplayAttributeData MaxHealth;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,MaxHealth);


	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Attributes")  
	FGameplayAttributeData Mana;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Mana);


	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Attributes")  
	FGameplayAttributeData MaxMana;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,MaxMana);


	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Stamina,Category="Attributes")  
	FGameplayAttributeData Stamina;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Stamina);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxStamina,Category="Attributes")  
	FGameplayAttributeData MaxStamina;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,MaxStamina);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="Attributes")  
	FGameplayAttributeData Strength;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Strength);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Endurance,Category="Attributes")  
	FGameplayAttributeData Endurance;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Endurance);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Agility,Category="Attributes")  
	FGameplayAttributeData Agility;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Agility);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence,Category="Attributes")
	FGameplayAttributeData Intelligence;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Intelligence);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Faith,Category="Attributes")
	FGameplayAttributeData Faith;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Faith);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Heal,Category="Attributes")  
	FGameplayAttributeData Heal;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Heal);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor,Category="Attributes")  
	FGameplayAttributeData Armor;  
	ATTRIBUTE_ACCESSORS(UMyAttributeSetBase,Armor);

	
	
	//Func where logic of replication is defines for this one Health Attribute
	UFUNCTION()  
	virtual void OnRep_Health(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_MaxHealth(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Mana(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_MaxMana(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Stamina(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_MaxStamina(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Strength(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Endurance(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Agility(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Intelligence(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Faith(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Heal(FGameplayAttributeData& OldValue);
	UFUNCTION()  
	virtual void OnRep_Armor(FGameplayAttributeData& OldValue);

	//Tell engine which property's should be replicated 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;
	
};

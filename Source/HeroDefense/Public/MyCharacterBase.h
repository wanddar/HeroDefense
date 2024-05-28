// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacterBase.generated.h"

class UMyGameplayAbility;
class UMyAttributeSetBase;
class UMyAbilitySystemComponent;

UCLASS()
class HERODEFENSE_API AMyCharacterBase : public ACharacter ,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	//GAS
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	UMyAttributeSetBase* AttributeSet;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Gameplay")  
	TSubclassOf<UGameplayEffect> AttrInitEffect;

	UPROPERTY(EditAnywhere,Category="Gameplay")  
	TArray<TSubclassOf<UMyGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere,Category="Gameplay")  
	TArray<TSubclassOf<UGameplayEffect>> PassiveEffects;

	UPROPERTY(EditAnywhere,Category="Gameplay")
	FGameplayTagContainer EffectTagsToRemoveOnDeath;

	UPROPERTY(EditAnywhere,Category="Gameplay")
	FGameplayTagContainer DrainStatusAbilitiesToCancel;

	UFUNCTION(BlueprintCallable,Category="Death")
	void RemoveControl();
	void Die();
	void OnHealthChangedInternal(const FOnAttributeChangeData& Data);
	void OnStaminaChangedInternal(const FOnAttributeChangeData& Data);
	void InitAttr() const;
	void GiveAbilities();

	bool bIsDead;
	FGameplayTagContainer Hit;

	//Overrides
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	
	// Sets default values for this character's properties
	AMyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

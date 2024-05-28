// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"


#include "Abilities/MyGameplayAbility.h"
#include "Attributes/MyAttributeSetBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/MyAbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"



class UMyGameplayAbility;
class UMyAttributeSetBase;
class UMyAbilitySystemComponent;



void AMyCharacterBase::RemoveControl()
{

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
		
	}

	if(AIControllerClass)
	{
		AIControllerClass.GetDefaultObject()->Destroy();
	}
	
}

void AMyCharacterBase::Die()
{
	//Off Collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Zero Velocity
	GetMovementComponent()->Velocity = FVector(0);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("ABS is Valid"));
		AbilitySystemComponent->CancelAllAbilities();

		//Remove all effects with tags in EffectTagsToRemoveOnDeath
		AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemoveOnDeath);

		if (AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Event.Death")))))
		{
			UE_LOG(LogTemp,Warning,TEXT("Ability is Activated Sucseseful"));
		}
		
	}


	RemoveControl();
	
}

void AMyCharacterBase::OnHealthChangedInternal(const FOnAttributeChangeData& Data)
{
	//Get Data
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;
	bool isHealing = OldHealth<=NewHealth;
	
	if (NewHealth <= 0.0f and !bIsDead)
	{
	
		UE_LOG(LogTemp, Warning, TEXT("Die: OldHealth:%f , NewHealth%f "), OldHealth, NewHealth);
		//Call function with Death logic 
		Die();
		bIsDead = true;
	}

	else
	{
		if (AbilitySystemComponent and !isHealing)
		{
			//Activate ability which react to hit
			AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Event.GetHit"))));
		}
		
	}

}

void AMyCharacterBase::OnStaminaChangedInternal(const FOnAttributeChangeData& Data)
{
	const float NewValue = Data.NewValue;
	FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName("Status.Drained"));
	

	if (NewValue == 0)
	{
		AbilitySystemComponent->AddLooseGameplayTag(Tag);
		AbilitySystemComponent->CancelAbilities(&DrainStatusAbilitiesToCancel);
		
	}
}

void AMyCharacterBase::InitAttr() const
{
	if (AttrInitEffect&&AbilitySystemComponent)  
	{  
		//Create Effect ContextHandle Context from ASC  
		const FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();  
		//Apply Init Effect  
		const UGameplayEffect* Effect = AttrInitEffect.GetDefaultObject();  
		AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect,1,EffectContextHandle);  
  
	}

	
	
}

void AMyCharacterBase::GiveAbilities()  
{  
	//If it is server  
	if (AbilitySystemComponent && HasAuthority())
	{       
		//for each ability in Abilities array
	
		int32 InputID = 0;
		for (TSubclassOf<UMyGameplayAbility> Ability : Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(),1,InputID));
			InputID++;
		}

		for (const TSubclassOf<UGameplayEffect> Passive : PassiveEffects)
		{
			const UGameplayEffect* Effect = Passive->GetDefaultObject<UGameplayEffect>();
			FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
			
			AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect,1,Context);
		}
	}  
}

UAbilitySystemComponent* AMyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMyCharacterBase::PossessedBy(AController* NewController)  
{  
	Super::PossessedBy(NewController);  
    
	if(AbilitySystemComponent)  
	{       
		//Tell engine that this(first) actor own ASC;  
		//Tell Engine that this(second) actor is AvatarActor of ASC;        
		AbilitySystemComponent->InitAbilityActorInfo(this,this);  
	}
	InitAttr();
	GiveAbilities();
}

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create ASC Object attached to this Actor  
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));  
  
	//Set replication to true 
	AbilitySystemComponent->SetIsReplicated(true);  
  
	//Set replication mode to Full  
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	
	AttributeSet = CreateDefaultSubobject<UMyAttributeSetBase>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	bIsDead = false;

	if (AbilitySystemComponent)
	{
		//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()) get delegate of Health attribute
		//AddUObject(this, &AMyCharacterBase::OnHealthChangedInternal); Add new delegate which is our custom function
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AMyCharacterBase::OnHealthChangedInternal);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &AMyCharacterBase::OnStaminaChangedInternal);
	}
}

// Called every frame
void AMyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


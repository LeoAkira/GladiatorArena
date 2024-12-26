// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"

// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
}

UAbilitySystemComponent* ABasePlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasePlayerCharacter::GetHealth()
{
	return BaseAttributeSet->GetHealth();
}

float ABasePlayerCharacter::GetMaxHealth()
{
	return BaseAttributeSet->GetMaxHealth();
}

float ABasePlayerCharacter::GetCurrentHealthPercentage()
{
	return BaseAttributeSet->GetHealth() / BaseAttributeSet->GetMaxHealth();
}

float ABasePlayerCharacter::GetShieldDurability()
{
	return BaseAttributeSet->GetShieldDurability();
}

float ABasePlayerCharacter::GetMaxShieldDurability()
{
	return BaseAttributeSet->GetMaxShieldDurability();
}
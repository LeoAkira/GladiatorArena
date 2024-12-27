// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BasePlayerCharacter.generated.h"

UCLASS()
class GLADIATORARENA_API ABasePlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const class UBaseAttributeSet* BaseAttributeSet;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentHealthPercentage();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetShieldDurability();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxShieldDurability();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthValueChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnShieldDurabilityValueChanged();
};

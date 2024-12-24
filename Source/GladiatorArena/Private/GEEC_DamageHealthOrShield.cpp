// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_DamageHealthOrShield.h"
#include "BaseAttributeSet.h"

struct DamageCalculation
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ShieldDurability);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	DamageCalculation()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Health, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, ShieldDurability, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Damage, Source, true);
	}
};

static const DamageCalculation& GetDamageCalculation()
{
	static DamageCalculation DamageCalc;
	return DamageCalc;
}

UGEEC_DamageHealthOrShield::UGEEC_DamageHealthOrShield()
{
	RelevantAttributesToCapture.Add(GetDamageCalculation().HealthDef);
	RelevantAttributesToCapture.Add(GetDamageCalculation().ShieldDurabilityDef);
	RelevantAttributesToCapture.Add(GetDamageCalculation().DamageDef);
}

void UGEEC_DamageHealthOrShield::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float ShieldDurability = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageCalculation().ShieldDurabilityDef, EvaluateParameters, ShieldDurability);

	if (ShieldDurability > 0)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCalculation().ShieldDurabilityProperty, EGameplayModOp::Additive, -1.0f));
	}
	else
	{
		float Health = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageCalculation().DamageDef, EvaluateParameters, Health);

		float Damage = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageCalculation().DamageDef, EvaluateParameters, Damage);

		//If Damage is bigger than remaining Health, zero the health instead
		float DamageDealt = FMath::Min(Health, Damage);

		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCalculation().HealthProperty, EGameplayModOp::Additive, -DamageDealt));
	}
}

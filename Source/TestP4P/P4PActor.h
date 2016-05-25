// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "P4PActor.generated.h"

UCLASS()
class TESTP4P_API AP4PActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP4PActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "P4PTest")
	void P4pTest_OnStep(FVector oa, FVector ob, FVector oc, FVector od, FVector4 A1, FVector4& outA1);

	float distFunc(float a1, float a2, float d12, float t12);

	FVector4 jfFunc(FVector4 A, float ts[4], float ds[4]);

	float jfHelpFunc(float a1, float t12, float a2);

	void getInversMatrix(FMatrix src, FMatrix &res);
};

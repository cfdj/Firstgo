// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class FIRSTGO_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;

	UPROPERTY()
		class UParticleSystemComponent* OurParticleSystem;
	UPROPERTY(EditAnywhere) USceneComponent* SphereVisual;
	UPROPERTY() USceneComponent* LookAt; //so the camera is looking slightly in front of the player

	UPROPERTY() class USpotLightComponent* Light;
	UPROPERTY() class USpotLightComponent* Laser;

	UPROPERTY()
		class UCollidingPawnMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
};
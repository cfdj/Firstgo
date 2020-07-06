// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn1.h"

// Sets default values
APawn1::APawn1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawn1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawn1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawn1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


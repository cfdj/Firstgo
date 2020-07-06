// Fill out your copyright notice in the Description page of Project Settings.
#include "CollidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "Math/Color.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	//setting up what the camera looks at
	LookAt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraLookAt"));
	LookAt->SetupAttachment(RootComponent);
	LookAt->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	//Giving the player a flash light, positioned slightly in front of the player
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Torch"));
	Light->SetupAttachment(RootComponent);
	Light->SetRelativeLocation(FVector(26.0f, 0.0f, 0.0f));
	Light->SetInnerConeAngle(10.0f);
	Light->SetOuterConeAngle(45.0f);
	Light->SetLightBrightness(5000.0f);

	//Giving the player a coloured aiming light
	Laser = CreateDefaultSubobject<USpotLightComponent>(TEXT("Laser"));
	Laser->SetupAttachment(RootComponent);
	Laser->SetRelativeLocation(FVector(26.0f, 0.0f, 0.0f));
	Laser->SetInnerConeAngle(1.0f);
	Laser->SetOuterConeAngle(0.0f);
	Laser->SetLightColor(FLinearColor(0,1,0,1));

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(LookAt);
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.f, 0.0f));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;
	SpringArm->bDoCollisionTest=false;

	// Create a camera and attach to our spring arm
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create an instance of our movement component, and tell it to update our root component.
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAxis("MoveX", this, &ACollidingPawn::MoveForward);
	InInputComponent->BindAxis("MoveY", this, &ACollidingPawn::MoveRight);
	InInputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

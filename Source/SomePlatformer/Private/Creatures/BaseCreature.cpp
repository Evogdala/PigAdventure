// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/BaseCreature.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"

ABaseCreature::ABaseCreature()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->GravityScale = 1.3f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.1f;
}

void ABaseCreature::BeginPlay()
{
	Super::BeginPlay();

	MaxSpeed = MinSpeed + AdditionalSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MinSpeed;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlatformerMappingContext, 0);
		}
	}

	Score = 0;
}

void ABaseCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCreature::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABaseCreature::StopMoving);

		// Test Action
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Started, this, &ABaseCreature::TestPerforming);
	}
}

void ABaseCreature::Move(const FInputActionValue& Value)
{
	bIsMoving = true;

	FVector2D MovementVector = Value.Get<FVector2D>();
	
	Turning(Value);

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	if (GetCharacterMovement()->MaxWalkSpeed < MaxSpeed)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Red, FString::Printf(TEXT("%f"), GetCharacterMovement()->MaxWalkSpeed));
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Green, FString::Printf(TEXT("%f"), MaxSpeed));
		// Cap max speed
		GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(GetCharacterMovement()->MaxWalkSpeed + SpeedIncrease * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), MinSpeed, MaxSpeed);
	}
	
	LastVector = MovementVector;
}

void ABaseCreature::StopMoving(const FInputActionValue& Value)
{
	bIsMoving = false;

	GetCharacterMovement()->MaxWalkSpeed = MinSpeed;
}

void ABaseCreature::Turning(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.X < 0.0f && bIsFacingForward)
	{
		GetMesh()->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
		bIsFacingForward = false;
	}
	else if (MovementVector.X > 0.0f && !bIsFacingForward)
	{
		GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
		bIsFacingForward = true;
	}

	// Check the vector to decrease speed when turning
	if (LastVector != MovementVector)
	{
		GetCharacterMovement()->MaxWalkSpeed = MinSpeed;
	}
}

void ABaseCreature::TestPerforming(const FInputActionValue& Value)
{
	this->SetActorLocation(LastSavePointLocation);
}


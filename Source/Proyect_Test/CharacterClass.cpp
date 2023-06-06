// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterClass.h"

#include "BaseGizmos/GizmoElementShared.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACharacterClass::ACharacterClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	//Instantiating class components
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	//Set the location and rotation of the character mesh transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-90.0f), FQuat(FRotator(0.0F,-90.0F,0.0F)));

	//Attaching class Componet to the default character's Skeletal mesh Component
	SpringArmComp->SetupAttachment(GetMesh());
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//Setting class variables of the spring arm
	SpringArmComp->bUsePawnControlRotation = true;

	//Setting class variables of the character movement component
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	GetCharacterMovement()->MovementState.bCanCrouch = true;
}

// Called when the game starts or when spawned
void ACharacterClass::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Spawneado rey"));
}

// Called every frame
void ACharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterClass::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacterClass::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACharacterClass::EndSprint);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterClass::BeginCrounch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacterClass::EndCrouch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterClass::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterClass::StopJumping);
}

void ACharacterClass::MoveForward(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		//find out witch way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
	
}
void ACharacterClass::MoveRight(float AxisValue)
{
	if((Controller != nullptr) && (AxisValue != 0.0f))
	{
		//find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get Right Vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//add movement in that direction
		AddMovementInput(Direction,AxisValue);
	}
}

void ACharacterClass::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}
void ACharacterClass::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ACharacterClass::BeginCrounch()
{
	Crouch();
}
void ACharacterClass::EndCrouch()
{
	UnCrouch();
}
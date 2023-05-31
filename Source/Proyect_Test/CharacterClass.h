// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterClass.generated.h"

UCLASS()
class PROYECT_TEST_API ACharacterClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Spring arm component to follow the camera behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	//Player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;
	
	//Called for forward/backward input
	void MoveForward(float AxisValue);
	//Called for Left/Right input
	void MoveRight(float AxisValue);

	//Sets character Movement speed to sprint values
	void BeginSprint();
	//Sets character movement speed back to default speed value
	void EndSprint();
	
	//Request for character to crounch
	void BeginCrounch();
	//Request for character endCrounch
	void EndCrouch();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SelGamePlayerController.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FControllerInfo
{
	GENERATED_BODY()

public:
	FControllerInfo()
	{
		this->deathNum = 0;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int deathNum;
};



UCLASS()
class SELGAME_API ASelGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASelGamePlayerController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int deathNum;

	UFUNCTION(BlueprintCallable)
	void PlayerThunderHit();
	UFUNCTION(BlueprintImplementableEvent)
	void ReSpawn();
	UFUNCTION(BlueprintCallable)
	void AddDeathNum(); 

	UFUNCTION(BlueprintCallable)
	int32 GetDeathCount();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool finalArraive;
	//UFUNCTION(BlueprintCallable)
	void FinalArraive();
private: 
};

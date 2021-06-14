// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FibMatrix.h"
#include "ThunderWeather.generated.h"

UCLASS()
class SELGAME_API AThunderWeather : public AActor
{
	GENERATED_BODY()
	
private: 
	bool bStarted = false;
	FibMatrix fib;
public:	
	// Sets default values for this actor's properties
	AThunderWeather();
	
	int32 ThunderIdx = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> ThunderSeq;

	// cm
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TileSize {
		500, 500, 1
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridWidth = 9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridHeight = 9;

	// seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ThunderGap = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float default_sym_z = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float sym_z_offset = 50.0f;

	UFUNCTION(BlueprintCallable)
	FVector GetLocationFromBlockIdx(int32 GridAddress);


	UFUNCTION(BlueprintCallable)
	void ProcessParticleColl(FVector loc, FVector v);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ParticleTraceDis = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ThunderPos = FVector(0, 0, 5000);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ThunerOneTimeCount = 3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SeqLength = 100;
	UFUNCTION(BlueprintCallable)
		TArray<int32> GetInitThunderSeq();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 min_path = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 block_cnt = 5;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartThunder();


	FTimerHandle TimerHandle_DefaultTimer;
	void GenThunderOnce();

	void GenThunder();

	UFUNCTION(BlueprintImplementableEvent)
	void BPGenThunder(FVector Loc);

	UFUNCTION(BlueprintImplementableEvent)
		void BPGenBlockSymbol(int32 idx, FVector Loc, bool blockOrNot);

};

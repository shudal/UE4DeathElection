// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "IThunderHit.generated.h" 

UINTERFACE(MinimalAPI, Blueprintable)
class UThunderHit : public UInterface
{
	GENERATED_BODY()
};
 
/**
 * 
 */
class SELGAME_API IThunderHit
{
	GENERATED_BODY()
public: 
	virtual void BeHit();
	virtual int32 GetDeathCount();
};

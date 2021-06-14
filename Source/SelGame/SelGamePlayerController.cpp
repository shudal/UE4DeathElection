// Fill out your copyright notice in the Description page of Project Settings.

#include "SelGamePlayerController.h"

ASelGamePlayerController::ASelGamePlayerController()
{
	/*
	this->isDeath = false;
	this->needReSpawn = false;
	*/
	this->deathNum = 0;
	this->finalArraive = false;
}

void ASelGamePlayerController::PlayerThunderHit()
{
	AddDeathNum();
	ReSpawn();
}

void ASelGamePlayerController::AddDeathNum()
{
	this->deathNum += 1;
}

int32 ASelGamePlayerController::GetDeathCount() {
	
	return deathNum;
}

void ASelGamePlayerController::FinalArraive()
{
	this->finalArraive = true;
}
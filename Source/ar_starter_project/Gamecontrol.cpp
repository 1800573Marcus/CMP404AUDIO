// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamecontrol.h"

void UGamecontrol::setgamestart(bool seter) {

	gamestart = seter;
}

bool UGamecontrol::getgamestart() {

	return gamestart;
}
void UGamecontrol::setgameend(bool seter) {

	gameend = seter;
}

bool UGamecontrol::getgameend() {

	return gameend;
}
void UGamecontrol::setspawnenemy(bool seter) {

	spawnenemy = seter;
}

bool UGamecontrol::getspawnenemy() {

	return spawnenemy;
}


void UGamecontrol::setspawnlocation(FVector start) {

	spawnlocation = start;
}

FVector UGamecontrol::getspawnlocation() {

	return spawnlocation;
}
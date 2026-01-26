// Fill out your copyright notice in the Description page of Project Settings.


#include "FloodWorldSave.h"

void UFloodWorldSave::set(FSave data) {
	save = data;
}

FSave UFloodWorldSave::get() {
	return save;
}

void UFloodWorldSave::clearSave() {
	save = FSave();
}

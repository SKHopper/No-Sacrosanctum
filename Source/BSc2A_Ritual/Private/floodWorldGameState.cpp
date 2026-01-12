// Fill out your copyright notice in the Description page of Project Settings.


#include "floodWorldGameState.h"
#include "Kismet/GameplayStatics.h"
#include "floodBoard.h"


AfloodWorldGameState::AfloodWorldGameState() {

	//

}

void AfloodWorldGameState::BeginPlay() {

	auto linkBoards = [](
		UWorld* world,
		TSubclassOf<AfloodBoard>boardClass,
		IfloodIF* self
	) {
		TArray<AActor*> boardActors;
		UGameplayStatics::GetAllActorsOfClass(world, boardClass, boardActors);

		for (AActor* board : boardActors) {
			Cast<IfloodIF>(board)->conveyGameState(self);
		}
	};

	linkBoards(GetWorld(), floodBoardClass, this);
}

void AfloodWorldGameState::bodyFilled() {

	gameFailed(true);

}
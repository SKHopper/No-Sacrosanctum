


#include "saver.h"
#include "FloodWorldSave.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
Asaver::Asaver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Asaver::BeginPlay()
{
	Super::BeginPlay();


	save = Cast<UFloodWorldSave>(UGameplayStatics::CreateSaveGameObject(UFloodWorldSave::StaticClass()));
}

// Called every frame
void Asaver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Asaver::write(FSave data) {
	save->set(data);
	UGameplayStatics::SaveGameToSlot(save, slot, 0);
}

FSave Asaver::read() {
	save = Cast<UFloodWorldSave>(UGameplayStatics::LoadGameFromSlot(slot, 0));
	if (save) {
		return save->get();
	}
	return FSave();
}

void Asaver::clear() {
	write(FSave());
}
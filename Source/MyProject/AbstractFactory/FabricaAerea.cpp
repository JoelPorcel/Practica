#include "FabricaAerea.h"
#include "Engine/World.h"
#include "../PlataformaAerea.h"
#include "../PlataformaLigera.h"

UFabricaAerea::UFabricaAerea()
{
}

APlataforma* UFabricaAerea::createA(FVector Location)
{
	return GetWorld()->SpawnActor<APlataformaAerea>(Location, FRotator::ZeroRotator);
}

APlataforma* UFabricaAerea::createB(FVector Location)
{
	return GetWorld()->SpawnActor<APlataformaLigera>(Location, FRotator::ZeroRotator);
}

#include "FabricaTrampa.h"
#include "Engine/World.h"
#include "../PlataformaTerrestre.h"
#include "../PlataformaTrampa.h"

UFabricaTrampa::UFabricaTrampa()
{
}

APlataforma* UFabricaTrampa::createA(FVector Location)
{
	return GetWorld()->SpawnActor<APlataformaTerrestre>(Location, FRotator::ZeroRotator);
}

APlataforma* UFabricaTrampa::createB(FVector Location)
{
	return GetWorld()->SpawnActor<APlataformaTrampa>(Location, FRotator::ZeroRotator);
}

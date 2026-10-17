#include "FabricaHierro.h"
#include "Engine/World.h"
#include "../PlataformaDestructible.h"
#include "../PlataformaIndestructible.h"

UFabricaHierro::UFabricaHierro()
{
}

APlataforma* UFabricaHierro::createA(FVector Location)
{
	return GetWorld()->SpawnActor<APlataformaDestructible>(Location, FRotator::ZeroRotator);
}

APlataforma* UFabricaHierro::createB(FVector Location)
{
	return GetWorld()->SpawnActor<APlataformaIndestructible>(Location, FRotator::ZeroRotator);
}

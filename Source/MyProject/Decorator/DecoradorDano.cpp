#include "DecoradorDano.h"

UDecoradorDano::UDecoradorDano()
{
}

float UDecoradorDano::GetDano()
{
	return Super::GetDano() + 25.0f;
}

FString UDecoradorDano::GetDescripcion()
{
	return Super::GetDescripcion() + TEXT(" + [Cañon Pesado]");
}

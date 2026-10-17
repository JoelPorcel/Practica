#include "DecoradorEscudo.h"

UDecoradorEscudo::UDecoradorEscudo()
{
}

float UDecoradorEscudo::GetEscudo()
{
	return Super::GetEscudo() + 100.0f;
}

FString UDecoradorEscudo::GetDescripcion()
{
	return Super::GetDescripcion() + TEXT(" + [Escudo Deflector]");
}

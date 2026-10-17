#include "DecoradorVelocidad.h"

UDecoradorVelocidad::UDecoradorVelocidad()
{
}

float UDecoradorVelocidad::GetVelocidad()
{
	return Super::GetVelocidad() + 1500.0f;
}

FString UDecoradorVelocidad::GetDescripcion()
{
	return Super::GetDescripcion() + TEXT(" + [Turbo]");
}

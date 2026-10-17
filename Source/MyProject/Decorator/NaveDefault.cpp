#include "NaveDefault.h"

UNaveDefault::UNaveDefault()
{
}

float UNaveDefault::GetVelocidad()
{
	return 2000.0f;
}

float UNaveDefault::GetDano()
{
	return 10.0f;
}

float UNaveDefault::GetEscudo()
{
	return 0.0f;
}

FString UNaveDefault::GetDescripcion()
{
	return TEXT("Nave Estandar");
}

#include "BaseDecorator.h"

UBaseDecorator::UBaseDecorator()
{
	Componente = nullptr;
	ComponenteObjeto = nullptr;
}

void UBaseDecorator::SetComponente(IDecorator* InComponente)
{
	Componente = InComponente;
	ComponenteObjeto = Cast<UObject>(InComponente);
}

IDecorator* UBaseDecorator::GetComponente()
{
	return Componente;
}

float UBaseDecorator::GetVelocidad()
{
	if (Componente)
	{
		return Componente->GetVelocidad();
	}
	return 2000.0f;
}

float UBaseDecorator::GetDano()
{
	if (Componente)
	{
		return Componente->GetDano();
	}
	return 10.0f;
}

float UBaseDecorator::GetEscudo()
{
	if (Componente)
	{
		return Componente->GetEscudo();
	}
	return 0.0f;
}

FString UBaseDecorator::GetDescripcion()
{
	if (Componente)
	{
		return Componente->GetDescripcion();
	}
	return TEXT("Decorador Base");
}

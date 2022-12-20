#include "jsPropellant.h"


namespace js
{
	Propellant::Propellant()
	{
	}
	Propellant::Propellant(Pos pos)
	{
	}
	Propellant::~Propellant()
	{
	}
	// Propellant.bmp
	void Propellant::Initialize()
	{
		SetImage(L"GoldBox", L"..\\Resources\\Image\\EventObject\\Propellant.bmp");

	}
	void Propellant::Tick()
	{
	}
	void Propellant::Render(HDC hdc)
	{
	}
	void Propellant::OnCollisionEnter(Collider* other)
	{
	}
	void Propellant::OnCollisionStay(Collider* other)
	{
	}
	void Propellant::OnCollisionExit(Collider* other)
	{
	}
	void Propellant::Push()
	{
	}
}
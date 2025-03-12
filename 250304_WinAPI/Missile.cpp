#include "Missile.h"
#include "CommonFunction.h"

void Missile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	color = RGB(255, 255, 255);
	moveSpeed = 3.0f;
	angle = 90.0f;
	size = 20;
	//destination;
}

void Missile::Release()
{
}

void Missile::Update()
{
	Move();
	if (isActived && IsOutofScreen())
	{
		isActived = false;
	}
}

void Missile::Render(HDC hdc)
{
	if (isActived)
	{
		RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	}
}

void Missile::Move()
{
	if (isActived)
	{
		pos.x += moveSpeed * cosf(DEG_TO_RAD(angle));
		pos.y -= moveSpeed * sinf(DEG_TO_RAD(angle));
	}
}

bool Missile::IsOutofScreen()
{
	float right = pos.x + size / 2;
	float left = pos.x - size / 2;
	float top = pos.y - size / 2;
	float bottom = pos.y + size / 2;

	if (right < 0 || left > WINSIZE_X 
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

Missile::Missile()
{
}

Missile::~Missile()
{
}

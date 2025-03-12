#include "AttractingBall.h"
#include "CommonFunction.h"

void AttractingBall::Init(FPOINT _pos, float _dir)
{
	this->pos = _pos;
	this->dir = _dir;
	this->isActivated = true;
}

void AttractingBall::Release()
{
}

void AttractingBall::Update()
{
	if (isStarted == false) {
		Move();
	}
	else Attract();
	
	
	if (IsOutofScreen()) {
		this->isActivated = false;
	}
}

void AttractingBall::Render(HDC hdc)
{
	if (isActivated == true) {
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, ballBrush);
		RenderEllipseAtCenter(hdc, pos.x, pos.y, innerSize, innerSize);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hOldBrush);
	}
	
}

void AttractingBall::CheckTheRange()
{
	
}

void AttractingBall::Move()
{
	if (isActivated)
	{
		pos.x += moveSpeed * cosf(DEG_TO_RAD(dir));
		pos.y -= moveSpeed * sinf(DEG_TO_RAD(dir));
	}
}

FPOINT AttractingBall::Attract()
{
	if (isActivated) {
		CheckTheRange();
	}

	return { 0,0 };
}

bool AttractingBall::IsOutofScreen()
{
	float right = pos.x + innerSize / 2;
	float left = pos.x - innerSize / 2;
	float top = pos.y - innerSize / 2;
	float bottom = pos.y + innerSize / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

AttractingBall::AttractingBall()
{
	this->pos = {WINSIZE_X+ 200, -100};
	this->dir = DEG_TO_RAD(90);
	innerSize = 10;
	rangeSize = 600;
	isStarted = false;
	isActivated = false;
	moveSpeed = 10.0f;

}

AttractingBall::~AttractingBall()
{
	DeleteObject(ballBrush);
}

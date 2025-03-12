#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"

void Enemy::Init()
{
	pos = { (float)(rand() % WINSIZE_X) /*/ 2 - 300*/, 150 };
	moveSpeed = 0.01f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	Move();
}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
		RenderRectAtCenter(hdc, pos.x, pos.y, size, size);
}

void Enemy::Move()
{
	if (target)
	{
		angle = GetAngle(pos, target->GetPos());

		pos.x += cosf(angle) * moveSpeed;
		pos.y += sinf(angle) * moveSpeed;
	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

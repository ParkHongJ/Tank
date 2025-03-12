#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "HP.h"

void Enemy::Init()
{
	pos = { WINSIZE_X / 2 - 300, 150 };
	moveSpeed = 0.01f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	maxHP = 100;
	hp = new HP(maxHP);
}

void Enemy::Release()
{
	delete hp;
}

void Enemy::Update()
{
	Move();
	hp->Update();
	IsDead();
}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		RenderRectAtCenter(hdc, pos.x, pos.y, size, size);
		
		FPOINT HPbarStartP = { pos.x - hp->GetMaxLength()/2, pos.y - (size/2+10)};
		hp->Render(hdc, HPbarStartP);
	}
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

void Enemy::IsDead()
{
	if (hp->GetNowNum() <= 0) {
		isAlive = false;
		hp->SetNowNum(0);
	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

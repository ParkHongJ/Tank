#pragma once
#include "config.h"
#define MAX_ROUND 3
class Enemy;
class GameObject;
class Fireworks;

struct Round
{
	int EnemyCount = 0;
	int Hp = 0;
	float EnemySpeed = 0.f;
};

class EnemyController
{
public:
	EnemyController() {};
	~EnemyController() {};

public:
	void Init(GameObject* Tank);
	void Update();
	void Render(HDC hdc);
	void Release();
	void AttackEnemy(Enemy* enemy, int Damage);
	Enemy** GetEnemies(OUT int& EnemyCount);

private:
	bool StartRound();
	void ReleaseEnemies(int round);
	void InitEnemy(const Round& round);

private:
	Round Rounds[MAX_ROUND];
	GameObject* Target = nullptr;
	//적들
	Enemy** Enemies = nullptr;
	int CurrentEnemyCount = 0;
	int CurrentRound = -1;
	bool isRoundEnded = true;
	wchar_t szText[128];
	bool bClear = false;

	Fireworks* fireWorks = nullptr;
};


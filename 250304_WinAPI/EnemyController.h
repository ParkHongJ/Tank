#pragma once
#include "config.h"

class Enemy;
class GameObject;

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
	void DestroyEnemy(Enemy* destroyEnemy);
	void AttackEnemy(Enemy* enemy, int Damage);
	Enemy** GetEnemies(int& EnemyCount);
private:
	bool StartRound();
	void ReleaseEnemies(int round);
	void InitEnemy(const Round& round);

private:
	Round Rounds[3];
	GameObject* Target = nullptr;
	//현재 실행중인 라운드의 적들이 담긴다
	Enemy** Enemies = nullptr;
	int CurrentEnemyCount = 0;
	int CurrentRound = -1;
	bool isRoundEnded = true;
	wchar_t szText[128];
};


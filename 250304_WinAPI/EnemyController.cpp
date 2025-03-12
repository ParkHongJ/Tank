#include "EnemyController.h"
#include "Enemy.h"
#include "Fireworks.h"

void EnemyController::Init(GameObject* Tank)
{
	//3 round
	Rounds[0].EnemyCount = 1;
	Rounds[0].Hp = 100;
	Rounds[0].EnemySpeed = 0.15f;
	
	Rounds[1].EnemyCount = 3;
	Rounds[1].Hp = 130;
	Rounds[1].EnemySpeed = 0.45f;

	Rounds[2].EnemyCount = 5;
	Rounds[2].Hp = 150;
	Rounds[2].EnemySpeed = 0.65f;

	Target = Tank;
	StartRound();

	fireWorks = new Fireworks;
	fireWorks->Init();
}

void EnemyController::Update()
{
	if (isRoundEnded == true && StartRound() == false)
		return;

	for (int i = 0; i < Rounds[CurrentRound].EnemyCount; i++)
	{
		if (Enemies[i]->GetIsAlive()) Enemies[i]->Update();
	}


	if (isRoundEnded == true || bClear == false)
		return;

	fireWorks->Update();
}

void EnemyController::Render(HDC hdc)
{
	wsprintf(szText, TEXT("Current Round : %d"), CurrentRound);
	TextOut(hdc, 20, 60, szText, wcslen(szText));

	for (int i = 0; i < Rounds[CurrentRound].EnemyCount; i++)
	{
		if (Enemies[i]->GetIsAlive()) Enemies[i]->Render(hdc);
	}

	if (isRoundEnded == true || bClear == false)
		return;

	wsprintf(szText, TEXT("WIN"));
	TextOut(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, szText, wcslen(szText));

	fireWorks->Render(hdc);
}

void EnemyController::Release()
{
	fireWorks->Release();
	delete fireWorks;

	delete[] Enemies;
	Enemies = nullptr;
}

void EnemyController::AttackEnemy(Enemy* enemy, int Damage)
{
	for (int i = 0; i < Rounds[CurrentRound].EnemyCount; i++)
	{
		if (Enemies[i] == enemy)
		{
			Enemies[i]->GetDamaged(Damage);
			break;
		}
	}

	if (enemy->GetIsAlive())
		return;

	--CurrentEnemyCount;


	//라운드 종료
	if (CurrentEnemyCount <= 0)
	{
		isRoundEnded = true;
	}

	if (isRoundEnded && CurrentRound >= MAX_ROUND - 1)
	{
		isRoundEnded = false;
		bClear = true;
	}
}

Enemy** EnemyController::GetEnemies(OUT int& EnemyCount)
{
	EnemyCount = Rounds[CurrentRound].EnemyCount;
	return Enemies;
}

bool EnemyController::StartRound()
{
	if (Target == nullptr)
		return false;

	ReleaseEnemies(CurrentRound);
	
	++CurrentRound;
	
	InitEnemy(Rounds[CurrentRound]);

	CurrentEnemyCount = Rounds[CurrentRound].EnemyCount;

	isRoundEnded = false;

	return true;
}

void EnemyController::ReleaseEnemies(int round)
{
	if (Enemies == nullptr)
		return;

	for (int i = 0; i < Rounds[round].EnemyCount; i++)
	{
		Enemies[i]->Release();
		delete Enemies[i];
	}
}

void EnemyController::InitEnemy(const Round& round)
{
	Enemies = new Enemy * [round.EnemyCount];

	for (int i = 0; i < round.EnemyCount; i++)
	{
		Enemies[i] = new Enemy;
		Enemies[i]->Init();
		Enemies[i]->SetTarget((Tank*)Target);
		Enemies[i]->SetMoveSpeed(round.EnemySpeed);
		Enemies[i]->SetHp(round.Hp);
		//todo EnemySetup hp
	}
}

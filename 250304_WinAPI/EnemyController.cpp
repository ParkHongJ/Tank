#include "EnemyController.h"
#include "Enemy.h"
void EnemyController::Init(GameObject* Tank)
{
	//3 round
	Rounds[0].EnemyCount = 1;
	Rounds[0].Hp = 10;
	Rounds[0].EnemySpeed = 0.1f;
	
	Rounds[1].EnemyCount = 3;
	Rounds[1].Hp = 30;
	Rounds[1].EnemySpeed = 0.25f;

	Rounds[2].EnemyCount = 5;
	Rounds[2].Hp = 50;
	Rounds[2].EnemySpeed = 0.35f;

	Target = Tank;
	StartRound();
}

void EnemyController::Update()
{
	if (isRoundEnded == true)
	{
		//타겟이 없어서 실패함
		if (StartRound() == false)
		{
			return;
		}
	}

	for (int i = 0; i < Rounds[CurrentRound].EnemyCount; i++)
	{
		if (Enemies[i]->GetIsAlive()) Enemies[i]->Update();
	}
}

void EnemyController::Render(HDC hdc)
{
	wsprintf(szText, TEXT("Current Round : %d"), CurrentRound);
	TextOut(hdc, 20, 60, szText, wcslen(szText));

	for (int i = 0; i < Rounds[CurrentRound].EnemyCount; i++)
	{
		if (Enemies[i]->GetIsAlive()) Enemies[i]->Render(hdc);
	}
}

void EnemyController::Release()
{
	delete[] Enemies;
	Enemies = nullptr;
}

void EnemyController::DestroyEnemy(Enemy* destroyEnemy)
{
	//적 삭제

	for (int i = 0; i < Rounds[CurrentRound].EnemyCount; i++)
	{
		if (Enemies[i] == destroyEnemy)
		{
			Enemies[i]->SetIsAlive(false);
			break;
		}
	}

	--CurrentEnemyCount;

	//라운드끝
	if (CurrentEnemyCount <= 0)
	{
		isRoundEnded = true;
	}
}

Enemy** EnemyController::GetEnemies(OUT int& EnemyCount)
{
	EnemyCount = Rounds[CurrentRound].EnemyCount;
	return Enemies;
}

bool EnemyController::StartRound()
{
	//타겟이 없다면 라운드 생성 실패
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
		//todo EnemySetup
	}
}

#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include "EnemyController.h"
#include "CommonFunction.h"

/*
	실습1. 적 클래스 생성 ( 화면 밖, 랜덤한 위치)
	실습2. 적은 탱크를 향해 다가온다.
	실습3. 미사일 - 적, 적 - 탱크 충돌 처리
	실습4. 5번째 미사일 마다 유도미사일 발사
			(가장 가까운 적을 따라 가서 맞춘다.)
*///



void MainGame::Init()
{
	srand(time(NULL));

	tank = new Tank;
	tank->Init();

	int a = 10;

	enemyController = new EnemyController;
	enemyController->Init(tank);
}

void MainGame::Release()
{
	if (tank)
	{
		tank->Release();
		delete tank;
	}

	if (enemyController)
	{
		enemyController->Release();
		delete enemyController;
	}
}

void MainGame::Update()
{
	if (tank)	tank->Update();
	if (enemyController) enemyController->Update();

	// 충돌처리 미사일 <-> 적
	Missile* missile = tank->GetMissiles();

	int enemyCount = 0;
	Enemy** enemies = enemyController->GetEnemies(enemyCount);

	for (int i = 0; i < tank->GetMissileCount(); i++)
	{
		for (int j = 0; j < enemyCount; j++)
		{
			if (enemies[j]->GetIsAlive() && missile[i].GetIsActived())
			{
				float dist = GetDistance(enemies[j]->GetPos(), missile[i].GetPos());
				float r = enemies[j]->GetSize() / 2 + missile[i].GetSize() / 2;

				if (dist < r)
				{
					enemyController->DestroyEnemy(enemies[j]);
					/*enemies[j]->SetIsAlive(false);*/
					missile[i].SetIsActived(false);
				}
			}
		}		
	}
}

void MainGame::Render(HDC hdc)
{

	if (tank)	tank->Render(hdc);
	if (enemyController) enemyController->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 10, NULL);

		break;
	case WM_TIMER:
		this->Update();

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			tank->RotateBarrel(2);
			break;
		case 'd': case 'D':
			tank->RotateBarrel(-2);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		if (tank)
		{
			tank->Fire();
		}
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

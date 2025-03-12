#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include "EnemyController.h"
#include "CommonFunction.h"
#include "HP.h"
#include "AttractingBall.h"

void MainGame::Init()
{
	srand(time(NULL));

	tank = new Tank;
	tank->Init();

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

					//enemies[j]->GetHP()->BeAttacked(missile[i].Attack());
					enemyController->AttackEnemy(enemies[j], missile[i].Attack());
					//enemy->GetHP()->BeAttacked(missile[i].Attack());
					//enemyController->DestroyEnemy(enemies[j]);
					/*enemies[j]->GetHP()->BeAttacked(missile[i].Attack());*/
					missile[i].SetIsActived(false);
				}
			}
		}
	}

	if (tank->GetBall()->GetIsStarted() == true) {
		for (int j = 0; j < enemyCount; j++)
		{
			if (enemies[j]->GetIsAlive())
			{
				float dist = GetDistance(enemies[j]->GetPos(), tank->GetBall()->GetPos());
				float r = enemies[j]->GetSize() / 2 + tank->GetBall()->GetRangeSize() / 2;
				float r2 = enemies[j]->GetSize() / 2 + tank->GetBall()->GetInnerSize() / 2;

				if (dist < r && dist >= r2)
				{
					enemies[j]->SetAttractedTo(tank->GetBall());
					enemies[j]->SetBeingAttracted(true);
					continue;
				}

				else if (dist < r2) {
					enemies[j]->SetAttractedTo(nullptr);
					enemies[j]->SetBeingAttracted(false);
				}

			}
		}

	}


	else if (tank->GetBall()->GetIsStarted() == false) {
		for (int j = 0; j < enemyCount; j++)
		{
			if (enemies[j]->GetIsAlive())
			{
				enemies[j]->SetAttractedTo(nullptr);
				enemies[j]->SetBeingAttracted(false);
			}
		}
	}
}
	


void MainGame::Render(HDC hdc)
{

	if (tank)	tank->Render(hdc);
	if (enemyController) enemyController->Render(hdc);
	//ball->Render(hdc);
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

		InvalidateRect(g_hWnd, NULL, false);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			tank->RotateBarrel(5);
			break;
		case 'd': case 'D':
			tank->RotateBarrel(-5);
			break;

		case 'q': case 'Q':
			tank->FireAttractingBall();
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

		InvalidateRect(g_hWnd, NULL, false);
		break;
	case WM_PAINT:
		static HDC hdc, MemDC, tmpDC;
		static HBITMAP BackBit, oldBackBit;
		static RECT bufferRT;
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &bufferRT);
		MemDC = CreateCompatibleDC(hdc);
		BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
		PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;

		this->Render(hdc);



		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		GetClientRect(hWnd, &bufferRT);
		BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
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

#include "HP.h"

void HP::BeAttacked(int attNum)
{
	if (isFull == true) {
		this->nowNum -= attNum;
		isFull = false;
	}

	else this->nowNum -= attNum;
}

float HP::CaculateForBar()
{
	nowLength = (float)nowNum * maxLength / (float)maxNum;
	return nowLength;
}

void HP::Init()
{

}

void HP::Release()
{
}

void HP::Update()
{
	CaculateForBar();
}

void HP::Render(HDC hdc, FPOINT pos)
{
	if (isFull == false) {
		HPEN hOldPen = (HPEN)SelectObject(hdc, hpBackgroundPen);
		MoveToEx(hdc, pos.x, pos.y, NULL); // 시작 좌표 설정
		LineTo(hdc, pos.x + maxLength, pos.y);  // 끝 좌표 설정 후 선 그리기

		SelectObject(hdc, nowHpPen);
		MoveToEx(hdc, pos.x, pos.y, NULL); //
		LineTo(hdc, pos.x + nowLength, pos.y);

		SelectObject(hdc, hOldPen);
	}
	

}

HP::HP(int _maxHP)
{
	this->maxNum = _maxHP;
	this->nowNum = _maxHP;
	this->isFull = true;
}

HP::~HP()
{
	DeleteObject(hpBackgroundPen);
	DeleteObject(nowHpPen);
}

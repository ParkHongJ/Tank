#pragma once
#include "GameObject.h"

class HP: public GameObject
{
private:
	//HP Var
	int maxNum;
	int nowNum;
	bool isFull;

	//HP Bar
	const float maxLength{ 30 };
	float nowLength{ 30 };

	HPEN hpBackgroundPen = CreatePen(PS_SOLID, 5, RGB(50, 50, 50)); // È¸»ö Ææ
	HPEN nowHpPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0)); // ÃÊ·Ï Ææ

public:
	inline int GetMaxNum() { return maxNum; }
	
	inline int GetNowNum() { return nowNum; }
	void BeAttacked(int attNum);
	inline void BeHealed(int healNum) { this->nowNum += healNum; }
	inline void SetNowNum(int _nowNum) { this->nowNum = _nowNum; }

	inline float GetMaxLength() { return maxLength; }

	float CaculateForBar();

	void Init(); 
	void Release(); 
	void Update(); 
	void Render(HDC hdc, FPOINT pos);

	HP(int _maxHP);
	~HP();

};


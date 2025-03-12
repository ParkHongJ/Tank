#pragma once
#include "GameObject.h"

class Tank;
class HP;

class Enemy : public GameObject	// is-a
{
private:
	FPOINT pos;
	float moveSpeed;
	float angle;
	bool isAlive;
	int size;
	Tank* target;
	int maxHP;
	HP* hp;

public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void IsDead();

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive;
	}
	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	inline int GetSize() { return size; }

	inline HP* GetHP() { return hp; }

	Enemy();
	~Enemy();

};


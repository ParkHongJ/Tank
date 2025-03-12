#pragma once
#include "GameObject.h"

class Tank;
class HP;
class EnemyController;
class AttractingBall;
class Enemy : public GameObject	// is-a
{
private:
	FPOINT pos;
	float moveSpeed;
	float angle;
	bool isAlive;
	int size;
	Tank* target;
	AttractingBall* attractedTo;
	bool beingAttracted;
	int maxHP;
	HP* hp;
public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void BeAttracted();
	void IsDead();

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive;}

	inline void SetAttractedTo(AttractingBall* ball) { this->attractedTo = ball; }
	inline void SetBeingAttracted(bool b) { this->beingAttracted = b; }

	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	inline int GetSize() { return size; }
	inline HP* GetHP() { return hp; }
	inline void SetMoveSpeed(float speed) { moveSpeed = speed; }
	
	void GetDamaged(int Damage);
	Enemy();
	~Enemy();

};


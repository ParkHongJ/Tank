#pragma once
#include "GameObject.h"

class Tank;

struct EnemyInfo
{

};
class Enemy : public GameObject	// is-a
{
private:
	FPOINT pos;
	float moveSpeed;
	float angle;
	bool isAlive;
	int size;
	Tank* target;

public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive;
	}
	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	inline int GetSize() { return size; }
	inline void SetMoveSpeed(float speed) { moveSpeed = speed; }
	Enemy();
	~Enemy();

};


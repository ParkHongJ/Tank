#pragma once
#include "GameObject.h"
class AttractingBall:public GameObject
{
private:
	FPOINT pos;
	float dir;
	float innerSize;
	float rangeSize;
	bool isStarted;
	bool isActivated;
	float moveSpeed;
	float ballTimeCount;

	HBRUSH ballBrush = CreateSolidBrush(RGB(255, 200, 200));
	
	
public:
	inline void SetIsActivated(bool activated) { this->isActivated = activated; }
	inline bool GetIsActivated() { return isActivated; }

	inline void SetIsStarted(bool _is) { this->isStarted = _is; }
	inline bool GetIsStarted() { return isStarted; }
	
	inline FPOINT GetPos() { return pos; }

	inline float GetRangeSize() { return rangeSize; }

	inline float GetInnerSize() { return innerSize; }
	inline void SetInnerSize(int _size) { this->innerSize = _size; }
	

	void Init(FPOINT _pos, float _dir);
	void Release(); 
	void Update(); 
	void Render(HDC hdc);

	void CheckTheRange();
	void Move();
	void CountAttractTime();

	bool IsOutofScreen();

	AttractingBall();
	~AttractingBall();
};


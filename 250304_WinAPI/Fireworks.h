#pragma once
#include "GameObject.h"


class Particle : public GameObject
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	//파티클은 퍼블릭으로 열었다
	FPOINT pos;
	int size;
	float angle;
	bool isActived;
	float moveSpeed;
};
class Fireworks : public GameObject
{
public:
	Fireworks();
	~Fireworks();

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

private:
	Particle** Particles;
	bool bRun = false;
	const int ParticleNum = 102;
};


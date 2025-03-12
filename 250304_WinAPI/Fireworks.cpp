#include "Fireworks.h"
#include "CommonFunction.h"

Fireworks::Fireworks()
{
}

Fireworks::~Fireworks()
{
}

void Fireworks::Init()
{
	Particles = new Particle * [ParticleNum];
	for (int i = 0; i < ParticleNum; i++)
	{
		Particles[i] = new Particle;
		Particles[i]->Init();
	}
	Particles[0]->isActived = true;
	Particles[0]->angle = 90.f;
	Particles[0]->pos = {WINSIZE_X / 2, WINSIZE_Y};

	Particles[1]->isActived = true;
	Particles[1]->angle = 90.f;
	Particles[1]->pos = { WINSIZE_X / 2 - 200, WINSIZE_Y };

	Particles[2]->isActived = true;
	Particles[2]->angle = 90.f;
	Particles[2]->pos = { WINSIZE_X / 2 + 200, WINSIZE_Y };
}

void Fireworks::Release()
{
	for (int i = 0; i < ParticleNum; i++)
	{
		Particles[i]->Release();
		delete Particles[i];
	}
	delete[] Particles;
}

void Fireworks::Update()
{
	if (Particles[0]->pos.y <= 300.f && Particles[0]->isActived == false && bRun == false)
	{
		bRun = true;

		for (int i = 3; i < ParticleNum; i++)
		{
			Particles[i]->isActived = true;
			//set angle
			Particles[i]->angle = (360.f / (float)((ParticleNum - 3) / 3)) * (float)i;
			
			FPOINT basePos = Particles[0]->pos;
			if (i < 33)
			{
				basePos = Particles[0]->pos;
				basePos = Particles[0]->pos;
			}
			else if (i >= 33 && i < 66)
			{
				basePos = Particles[1]->pos;
				basePos = Particles[1]->pos;
			}
			else
			{
				basePos = Particles[2]->pos;
				basePos = Particles[2]->pos;
			}


			FPOINT newPos = { cosf(DEG_TO_RAD(Particles[i]->angle)), sinf(DEG_TO_RAD(Particles[i]->angle)) };
			newPos.x = basePos.x + newPos.x * 100.f;
			newPos.y = basePos.y - newPos.y * 100.f;

			Particles[i]->pos = newPos;
		}
	}

	for (int i = 0; i < ParticleNum; i++)
	{
		Particles[i]->Update();
	}
}

void Fireworks::Render(HDC hdc)
{
	for (int i = 0; i < ParticleNum; i++)
	{
		Particles[i]->Render(hdc);
	}
}

/*
	Particle
*/
void Particle::Init()
{
	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 5.0f;
	size = 50;
}

void Particle::Release()
{
}

void Particle::Update()
{
	if (isActived == false)
		return;

	pos.x += moveSpeed * cosf(DEG_TO_RAD(angle));
	pos.y -= moveSpeed * sinf(DEG_TO_RAD(angle));

	size -= 1;
	
	if (size <= 0)
	{
		isActived = false;
	}
}

void Particle::Render(HDC hdc)
{
	if (isActived)
	{
		RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	}
}

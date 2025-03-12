#pragma once
#include "config.h"

class GameObject
{
public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	GameObject();
	~GameObject();
};


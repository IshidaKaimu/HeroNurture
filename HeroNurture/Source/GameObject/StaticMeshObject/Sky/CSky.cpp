#include "CSky.h"

CSky::CSky()
{
	SetScale(100.0f, 100.0f, 100.0f);
	SetPosition(0.0f, 0.0f, 0.0f);
}

CSky::~CSky()
{
}

void CSky::Update()
{
	CStaticMeshObject::Update();
}

void CSky::Draw()
{
	CStaticMeshObject::Draw();
}


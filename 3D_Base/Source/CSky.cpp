#include "CSky.h"

CSky::CSky()
{
	SetScale(100.0f, 100.0f, 100.0f);
}

CSky::~CSky()
{
}

void CSky::Update()
{
	CStaticMeshObject::Update();
}


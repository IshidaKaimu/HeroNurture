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

void CSky::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CStaticMeshObject::Draw(View, Proj, Light, Camera);
}


#include "CGround.h"

CGround::CGround()
	: m_pPlayer	( nullptr )
{
	SetScale(1.0f, 1.0f, 1.0);
	SetPosition(0.0f, 0.0f, 0.0f);
}

CGround::~CGround()
{
	m_pPlayer = nullptr;
}

void CGround::Update()
{
	CStaticMeshObject::Update();
}

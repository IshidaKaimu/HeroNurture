#include "CGround.h"

CGround::CGround()
	: m_pPlayer	( nullptr )
{
}

CGround::~CGround()
{
	m_pPlayer = nullptr;
}

void CGround::Update()
{
	CStaticMeshObject::Update();
}

#include "CCharacter.h"

CCharacter::CCharacter()
	: m_pRayY   ( nullptr )
{
	m_pRayY = new RAY();
	m_pRayY->Axis = D3DXVECTOR3(0.0f, -1.0f, 0.0f);//‰ºŒü‚«‚ÌŽ²
	m_pRayY->Length = 10.0f;	//‚Æ‚è‚ ‚¦‚¸10‚É‚µ‚Ä‚¨‚­
}

CCharacter::~CCharacter()
{
	SAFE_DELETE( m_pRayY );
}

void CCharacter::Update()
{
	CStaticMeshObject::Update();
}

void CCharacter::Draw()
{
	CStaticMeshObject::Draw();
}

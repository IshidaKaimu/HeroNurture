#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include "KeyManager/CKeyManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
{
	m_pJson = std::make_unique<CJson>();
}

CHeroBase::~CHeroBase()
{
}

void CHeroBase::Update()
{
	CKeyManager::GetInstance()->Update();
}

void CHeroBase::Draw( LIGHT& Light )
{
	CSkinMeshObject::Draw( Light );
}

void CHeroBase::Animation()
{
}



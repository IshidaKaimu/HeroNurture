#include "CPlayer.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include "KeyManager/CKeyManager.h"

CPlayer::CPlayer()	
{
	SetScale(0.1f, 0.1f, 0.1f);
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetData()
{

}

void CPlayer::Update()
{

	CKeyManager::GetInstance()->Update();


	ImGui::Begin(JAPANESE("ÉpÉâÉÅÅ[É^"));
	ImGui::Text("Power::%d", m_Paramater.Power);
	ImGui::Text("Magic::%d", m_Paramater.Magic);
	ImGui::Text("Speed::%d", m_Paramater.Speed);
	ImGui::Text("HP::%d"   , m_Paramater.HP);
	ImGui::End();





}

void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera )
{
	CSkinMeshObject::Draw( View, Proj, Light, Camera );
}

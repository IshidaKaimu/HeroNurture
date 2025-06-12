#include "CLightManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CLightManager::CLightManager()
    : m_Light()
{
    //ライト位置の設定
    m_Light.Position   = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
    //ライト方向
    m_Light.vDirection = D3DXVECTOR3(0.0f, 7.0f, -5.0f);
    //ライト強度
    m_Light.Intensity  = 10.0f;
}

CLightManager::~CLightManager()
{
}

//デバッグ処理
void CLightManager::Debug()
{
    ImGui::Begin(JAPANESE("ライト"));
    ImGui::InputFloat3(JAPANESE("ライト方向"), m_DebugDirection);
    SetDir(m_DebugDirection);
    ImGui::End();
}

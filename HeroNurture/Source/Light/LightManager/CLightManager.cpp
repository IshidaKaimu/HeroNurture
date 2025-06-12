#include "CLightManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CLightManager::CLightManager()
    : m_Light()
{
    //���C�g�ʒu�̐ݒ�
    m_Light.Position   = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
    //���C�g����
    m_Light.vDirection = D3DXVECTOR3(0.0f, 7.0f, -5.0f);
    //���C�g���x
    m_Light.Intensity  = 10.0f;
}

CLightManager::~CLightManager()
{
}

//�f�o�b�O����
void CLightManager::Debug()
{
    ImGui::Begin(JAPANESE("���C�g"));
    ImGui::InputFloat3(JAPANESE("���C�g����"), m_DebugDirection);
    SetDir(m_DebugDirection);
    ImGui::End();
}

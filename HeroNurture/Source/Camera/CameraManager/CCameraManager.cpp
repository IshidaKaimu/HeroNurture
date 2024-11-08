#include "CCameraManager.h"

CCameraManager::CCameraManager()
    : m_pCamera()
{
    m_pCamera = std::make_unique<CCamera>();
}

CCameraManager::~CCameraManager()
{
}

//�J�����̍X�V����
void CCameraManager::CameraUpdate()
{
    m_pCamera->Update();
}

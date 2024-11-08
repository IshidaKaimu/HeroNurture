#include "CCameraManager.h"

CCameraManager::CCameraManager()
    : m_pCamera()
{
    m_pCamera = std::make_unique<CCamera>();
}

CCameraManager::~CCameraManager()
{
}

//ƒJƒƒ‰‚ÌXVˆ—
void CCameraManager::CameraUpdate()
{
    m_pCamera->Update();
}

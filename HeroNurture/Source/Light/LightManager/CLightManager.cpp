#include "CLightManager.h"

CLightManager::CLightManager()
    : m_Light()
{
    //ライト位置の設定
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //ライト方向
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //ライト強度
    m_Light.Intensity  = 1.0f;
}

CLightManager::~CLightManager()
{
}

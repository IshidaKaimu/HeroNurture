#include "CLightManager.h"

CLightManager::CLightManager()
    : m_Light()
{
    //���C�g�ʒu�̐ݒ�
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //���C�g����
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //���C�g���x
    m_Light.Intensity  = 1.0f;
}

CLightManager::~CLightManager()
{
}

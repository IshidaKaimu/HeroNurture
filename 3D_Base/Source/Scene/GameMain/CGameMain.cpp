#include "CGameMain.h"
#include "Scene/CSceneManager.h"
#include "KeyManager/CKeyManager.h"
#include "StaticMesh/MeshManager/CMeshManager.h"
#include "Sound/CSoundManager.h"
#include <cmath>
#include <fstream>
#include <sstream>

CGameMain::CGameMain()
    : m_pSky()
    , m_pGround()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time(-10.0f)
{
    m_Camera.Position = D3DXVECTOR3(0.0, 10.0, 0.0);
    m_Camera.Look = D3DXVECTOR3(0.0, 0.0, 0.0);

    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CGameMain::~CGameMain()
{
}

//�\�z�֐�
void CGameMain::Create()
{
    m_pSky = new CSky();
    m_pGround = new CGround();
}

//�f�[�^�ݒ�֐�
void CGameMain::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//�j���֐�
void CGameMain::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//�X�V�֐�
void CGameMain::Update()
{


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    m_Camera.Look = D3DXVECTOR3(m_pGround->GetPosition());

    CKeyManager::GetInstance()->Update();

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown('1'))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        if (m_Opening == true) {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
        }
    }


}

//�`��֐�
void CGameMain::Draw()
{
    m_mProj = CCamera::GetInstance()->GetProjection();
    m_mView = CCamera::GetInstance()->GetViewMatrix();


    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }


    float x = Easing(m_Time);

    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
}

//�C�[�W���O
float CGameMain::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

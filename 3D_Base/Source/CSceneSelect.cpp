#include "CSceneSelect.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CMeshManager.h"
#include "CSoundManager.h"
#include <cmath>

CSceneSelect::CSceneSelect()
    : m_pSky    ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
{
    Create();
    LoadData();
}

CSceneSelect::~CSceneSelect()
{
}

void CSceneSelect::Create()
{
    m_pSky = new CSky();
}

void CSceneSelect::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
}

void CSceneSelect::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�eBGM�̒�~
    CSoundManager::Stop(CSoundManager::BGM_Opening);    //�I�[�v�j���O
    CSoundManager::Stop(CSoundManager::BGM_BossApe);    //�{�X�o��V�[��
    CSoundManager::Stop(CSoundManager::BGM_BossEvo);    //�{�X�i���V�[��
    CSoundManager::Stop(CSoundManager::BGM_Special);    //�K�E�Z�V�[��
    CSoundManager::Stop(CSoundManager::BGM_BossDeath);  //�{�X���j�V�[��

    CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


    CKeyManager::GetInstance()->Update();


    

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown('1'))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }
    if (CKeyManager::GetInstance()->IsDown('2'))
    {
        //�{�X�o��V�[����
        m_SceneTransitionFlg = true;
        m_BossApp = true;
    }

    if (CKeyManager::GetInstance()->IsDown('3'))
    {
        //�{�X�i���V�[����
        m_SceneTransitionFlg = true;
        m_BossEvo = true;
    }

    if (CKeyManager::GetInstance()->IsDown('4'))
    {
        //�K�E�Z�V�[����
        m_SceneTransitionFlg = true;
        m_Special = true;
    }

    if (CKeyManager::GetInstance()->IsDown('5'))
    {
        //�{�X���j�V�[����
        m_SceneTransitionFlg = true;
        m_BossDeath = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        if (m_Opening == true) {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::Opening);
        }
        else if(m_BossApp == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::BossApp);
        }
        else if (m_BossEvo == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::BossEvo);
        }
        else if (m_Special == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::Special);
        }
        else if (m_BossDeath == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::BossDeath);
        }
    }


}

void CSceneSelect::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    m_pSky->Draw(View, Proj, Light, Camera);

    float x = Easing(m_Time);
    WriteText::GetInstance()->Draw_Text(L"1 Opening", WriteText::Select, D3DXVECTOR2(x, 0));
    WriteText::GetInstance()->Draw_Text(L"2 Boss Appearance", WriteText::Select, D3DXVECTOR2(x, 80));
    WriteText::GetInstance()->Draw_Text(L"3 Boss Evolution", WriteText::Select, D3DXVECTOR2(x, 160));
    WriteText::GetInstance()->Draw_Text(L"4 Special", WriteText::Select, D3DXVECTOR2(x, 240));
    WriteText::GetInstance()->Draw_Text(L"5 Boss Destroy", WriteText::Select, D3DXVECTOR2(x, 320));

}

//�C�[�W���O
float CSceneSelect::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

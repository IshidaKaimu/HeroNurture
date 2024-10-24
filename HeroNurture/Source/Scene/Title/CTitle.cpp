#include "CTitle.h"
#include "Scene/CSceneManager.h"
#include "KeyManager/CKeyManager.h"
#include "StaticMesh/MeshManager/CMeshManager.h"
#include "Sound/CSoundManager.h"
#include <cmath>
#include <iostream>
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>
#include <codecvt>

//�^�C�g���V�[��
CTitle::CTitle()
    : m_pSky    ()
    , m_pGround ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
    , m_pPlayer()
{
    //�J�����ʒu�����ݒ�
    CCamera::GetInstance()->SetPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    //�J���������_�����ݒ�
    CCamera::GetInstance()->SetLook(D3DXVECTOR3(0.0f, 0.0f, 4.0f));

    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CTitle::~CTitle()
{
}

//�\�z�֐�
void CTitle::Create()
{
    m_pSky = new CSky();
    m_pGround = new CGround();
    m_pPlayer = new CPlayer();
    m_pGameMain = new CGameMain();
}

//�f�[�^�ݒ�֐�
void CTitle::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//�j���֐�
void CTitle::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
    SAFE_DELETE(m_pGameMain);
}

//�X�V�֐�
void CTitle::Update()
{

    
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�U�[�����͏���
    InputName();

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        if (m_Opening == true) {
            //���[�U�[�l�[�����o�^����Ă�����
            if (!m_UserName.empty()) 
            {
                m_pGameMain->SetUserName(m_UserName);
                CSceneManager::GetInstance()->LoadCreate(CSceneManager::GameMain);
            }
            else
            {
                std::wcerr << L"���[�U�[�l�[�����ݒ肳��Ă��܂���B" << std::endl;
            }
        }
    }


}

//�`��֐�
void CTitle::Draw()
{

    CCamera::GetInstance()->Projection();
    CCamera::GetInstance()->Update();
    m_mProj = CCamera::GetInstance()->GetProjection();
    m_mView = CCamera::GetInstance()->GetViewMatrix();


    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //�n�ʂ̕`��
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //�����̓���
    WriteText::GetInstance()->Draw_Text(m_UserName, WriteText::Select, D3DXVECTOR2(0.0f, 0.0f));
}

//�C�[�W���O
float CTitle::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

//���O���͏���
void CTitle::InputName()
{
    //�L�[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    //�L�[�}�l�[�W���̏�ɍs������
    KeyMng->Update();

    //�L�[�S���𒲂ׂ�
    for (int key = 0x30; key <= 0x5A; key++)
    {
        if (KeyMng->IsDown(key))
        {
            //���͂��ꂽ������ǉ�
            m_UserName += wchar_t(key);
        }
    }

    //�e�L�X�g����ł͂Ȃ��Ȃ�
    if (!m_UserName.empty()) 
    {
        //�o�b�N�X�y�[�X�������ꂽ��
        if (KeyMng->IsDown(VK_BACK))
        {
            //�Ō�̕������폜
            m_UserName.pop_back();
        }
    }
}

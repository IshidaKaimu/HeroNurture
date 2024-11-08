#include "CGameMain.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include <cmath>
#include <fstream>
#include <sstream>


CGameMain::CGameMain()
    : m_pCamera (  &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_UserName()
    , m_pPlayer ()
{
}

CGameMain::~CGameMain()
{
}


//�\�z�֐�
void CGameMain::Create()
{
    //�X�J�C�{�b�N�X�̃C���X�^���X����
    m_pSky    = new CSky();
    //�n�ʂ̃C���X�^���X����
    m_pGround = new CGround();
    //�v���C���[�̃C���X�^���X����
    m_pPlayer = new CPlayer();


}

//�f�[�^�ݒ�֐�
void CGameMain::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();

    //�X�L�����b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CSkinMeshManager* SKMng = CSkinMeshManager::GetInstance();

    //�X�J�C�{�b�N�X�̃��b�V���ݒ�
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    //�n�ʂ̃��b�V���ݒ�
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
    //�v���C���[�̃��b�V���ݒ�
    m_pPlayer->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
    
}

//�j���֐�
void CGameMain::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
    SAFE_DELETE(m_pPlayer);
}

//�������֐�
void CGameMain::Initialize()
{
    //�v���C���[�̍��W����ϐ��ɑ��
    D3DXVECTOR3 PPos = m_pPlayer->GetPosition();

    //�����J�������W�̐ݒ�
    m_pCamera->Initialize();

    //���C�g���
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}


//�X�V�֐�
void CGameMain::Update()
{
    //�v���C���[�̍��W����ϐ��ɑ��
    D3DXVECTOR3 PPos = m_pPlayer->GetPosition();


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("�J�������W"),CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), CamLook);
    //m_pCamera->SetPos(CamPos);
    m_pCamera->SetLook(CamLook);

#endif

    
    m_pPlayer->Update();

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
      
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
    }
}

//�`��֐�
void CGameMain::Draw()
{  
    //�J�����̓���
    m_pCamera->CameraUpdate();
    
    //�v���C���[�̕`��
    m_pPlayer->Draw( m_Light );

    //��̕`��
    m_pSky->Draw( m_Light );

    //�n�ʂ̕`��
    m_pGround->Draw( m_Light );
}


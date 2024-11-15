#include "CGameMain.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include <cmath>
#include <fstream>
#include <sstream>


CGameMain::CGameMain()
    : m_pCamera (  &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_UserName()
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
    
}

//�j���֐�
void CGameMain::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//�������֐�
void CGameMain::Initialize()
{

    //�����J�������W�̐ݒ�
    m_pCamera->Initialize();

    //���C�g���
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}


//�X�V�֐�
void CGameMain::Update()
{

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("�J�������W"),CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), CamLook);
    //m_pCamera->SetPos(CamPos);
    m_pCamera->SetLook(CamLook);

#endif

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        CHeroManager::GetInstance().SelectHero(CHeroManager::Kaito);
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
    }
}

//�`��֐�
void CGameMain::Draw()
{  
    //�J�����̓���
    m_pCamera->CameraUpdate();
    
    //��̕`��
    m_pSky->Draw( m_Light );

    //�n�ʂ̕`��
    m_pGround->Draw( m_Light );
}


#include "CHeroSelect.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"
#include <cmath>
#include <fstream>
#include <sstream>


CHeroSelect::CHeroSelect()
    : m_pCamera (  &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_UserName()
    , m_SelectNo()
{
}

CHeroSelect::~CHeroSelect()
{
}


//�\�z�֐�
void CHeroSelect::Create()
{
   //----�C���X�^���X����----

   //----�q�[���[�N���X�̃C���X�^���X����----
   //���C
    m_pYui = new CYui();
   //�J�C�g
   m_pKaito = new CKaito();

    //�X�J�C�{�b�N�X�̃C���X�^���X����
    m_pSky    = new CSky();

    //�n�ʂ̃C���X�^���X����
    m_pGround = new CGround();
}

//�f�[�^�ݒ�֐�
void CHeroSelect::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();

    //�X�L�����b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CSkinMeshManager* SKMng = CSkinMeshManager::GetInstance();

    //�q�[���[�}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----�q�[���[�N���X�̃f�[�^�ǂݍ���----
    //���C
    m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
    //�J�C�g
    m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

    //�X�J�C�{�b�N�X�̃��b�V���ݒ�
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));

    //�n�ʂ̃��b�V���ݒ�
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
    
}

//�j���֐�
void CHeroSelect::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//�������֐�
void CHeroSelect::Initialize()
{

    //�����J�������W�̐ݒ�
    m_pCamera->Initialize();

#ifdef DEBUG
    CamPos  = D3DXVECTOR3(0.0f, 4.0f, -9.0f);
    CamLook = D3DXVECTOR3(0.0f, 4.0f, 3.0f);
#endif

    //���C�g���
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //�����I��
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����

    //----�e�q�[���[�N���X�̏�����----
    //���C
    m_pYui->Initialize();
    //�J�C�g
    m_pKaito->Initialize();

}

//�X�V�֐�
void CHeroSelect::Update()
{

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�L�[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CKeyManager* Key = CKeyManager::GetInstance();

    //�q�[���[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�L�[�}�l�[�W���̓��쏈��
    CKeyManager::GetInstance()->Update();

    //�J�[�\���̈ړ�
    if (Key->IsDown(VK_RIGHT))
    {
        //�L�[���͂őI����i�߂�
        if (m_SelectNo < CHeroBase::enCharacterList::max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (Key->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("�J�������W"),CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), CamLook);
    CCameraManager::GetInstance().SetPos(CamPos);
    CCameraManager::GetInstance().SetLook(CamLook);
#endif

#ifdef _DEBUG
    ImGui::Begin(JAPANESE("�I����"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("���C")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("�J�C�g")); }
    ImGui::End();
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
        switch (m_SelectNo)
        {
        case 0:
            Hero->SelectHero(CHeroManager::Yui);
            break;
        case 1:
            Hero->SelectHero(CHeroManager::Kaito);
            break;
        default:
            break;
        }
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
    }
}

//�`��֐�
void CHeroSelect::Draw()
{  
    //�J�����̓���
    m_pCamera->CameraUpdate();
    
    //��̕`��
    m_pSky->Draw( m_Light );

    //�n�ʂ̕`��
    m_pGround->Draw( m_Light );

    //�q�[���[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�I�𒆃q�[���[�̕`��E�A�j���[�V�����E�J�����z�u
    switch (m_SelectNo)
    {
    case 0:
        //���C
        m_pYui->Animation();
        m_pCamera->SetPos(CAMPOS_YUI);
        m_pCamera->SetLook(CAMLOOK_YUI);
        m_pYui->Draw(m_Light);
        break;
    case 1:
        //�J�C�g
        m_pKaito->Animation();
        m_pCamera->SetPos(CAMPOS_YUI);
        m_pCamera->SetLook(CAMLOOK_YUI);
        m_pKaito->Draw(m_Light);
        break;
    default:
        break;
    }

}


#include "CNatureHeroSelectScene.h"
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


CNatureHeroSelectScene::CNatureHeroSelectScene()
    : m_pCamera (  &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_UserName()
{
}

CNatureHeroSelectScene::~CNatureHeroSelectScene()
{
}

//�\�z�֐�
void CNatureHeroSelectScene::Create()
{
   //----�q�[���[�N���X�̃C���X�^���X����----
   //���C
    m_pYui    = make_unique<CYui>();
   //�J�C�g
   m_pKaito   = make_unique<CKaito>();

   //�X�J�C�{�b�N�X�̃C���X�^���X����
   m_pSky    = make_unique<CSky>();

   //�n�ʂ̃C���X�^���X����
   m_pGround = make_unique<CGround>();
}

//�f�[�^�ݒ�֐�
void CNatureHeroSelectScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    CSkinMeshManager* SKMng = CSkinMeshManager::GetInstance();
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----�e�q�[���[�N���X�̃��b�V���f�[�^�ݒ�----
    //���C
    m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
    //�J�C�g
    m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

    //�X�J�C�{�b�N�X�̃��b�V���f�[�^�ݒ�
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));

    //�n�ʂ̃��b�V���ݒ�
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
    
}

//�j���֐�
void CNatureHeroSelectScene::Releace()
{
}

//�������֐�
void CNatureHeroSelectScene::Initialize()
{

#ifdef DEBUG
    CamPos  = D3DXVECTOR3(0.0f, 4.0f, -9.0f);
    CamLook = D3DXVECTOR3(0.0f, 4.0f, 3.0f);
#endif

    //�J�����ʒu�̐ݒ�
    m_pCamera->SetPos(CAMPOS_NS);
    //�J�����̒����_�̐ݒ�
    m_pCamera->SetLook(CAMLOOK_NS);

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
void CNatureHeroSelectScene::Update()
{

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = CKeyManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�L�[�}�l�[�W���̓��쏈��
    CKeyManager::GetInstance()->Update();

    //�J�[�\���̈ړ�
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //�L�[���͂őI����i�߂�
        if (m_SelectNo < CHeroBase::enHeroList::Max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
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
            HeroMng->SelectHero(CHeroManager::Yui);
            break;
        case 1:
            HeroMng->SelectHero(CHeroManager::Kaito);
            break;
        default:
            break;
        }
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
    }
}

//�`��֐�
void CNatureHeroSelectScene::Draw()
{  
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�J�����̓���
    m_pCamera->CameraUpdate();
    
    //��̕`��
    m_pSky->Draw();

    //�n�ʂ̕`��
    m_pGround->Draw();

    //�I�𒆃q�[���[�̕`��E�A�j���[�V�����E�J�����z�u
    switch (m_SelectNo)
    {
    case 0:
        //���C
        m_pYui->NatureHeroSelectAnimation();
        m_pYui->Draw();
        break;
    case 1:
        //�J�C�g
        m_pKaito->NatureHeroSelectAnimation();
        m_pKaito->Draw();
        break;
    default:
        break;
    }

}


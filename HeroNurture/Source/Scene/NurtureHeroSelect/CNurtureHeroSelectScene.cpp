#include "CNurtureHeroSelectScene.h"
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
#include "Sprite2D\UIManager\CUIManager.h"
#include <cmath>
#include <fstream>
#include <sstream>

//�萔�̖��O���
using namespace Constant_NurtureHeroSelectScene;

CNurtureHeroSelectScene::CNurtureHeroSelectScene()
    : m_pCamera    (&CCameraManager::GetInstance())
    , m_pYui       ()
    , m_pKaito     ()
    , m_UserName   ()
    , m_pLeftArrow ()
    , m_pRightArrow()
{
}

CNurtureHeroSelectScene::~CNurtureHeroSelectScene()
{
}

//�\�z�֐�
void CNurtureHeroSelectScene::Create()
{
   //----�X�L�����b�V��----
    m_pYui    = make_unique<CYui>();  //���C
   m_pKaito   = make_unique<CKaito>();//�J�C�g

   //----UI----
   m_pLeftArrow  = make_unique<CUIObject>(); //�����
   m_pRightArrow = make_unique<CUIObject>(); //�E���
}

//�f�[�^�ݒ�֐�
void CNurtureHeroSelectScene::LoadData()
{
    //----�e�q�[���[�N���X�̃��b�V���f�[�^�ݒ�----
    m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));    //���C
    m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));//�J�C�g

    //----UI----
    m_pLeftArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow)); //���
    m_pRightArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow));//���E
}

//�j���֐�
void CNurtureHeroSelectScene::Releace()
{
}

//�������֐�
void CNurtureHeroSelectScene::Initialize()
{

#ifdef DEBUG
    CamPos  = D3DXVECTOR3(0.0f, 4.0f, -9.0f);
    CamLook = D3DXVECTOR3(0.0f, 4.0f, 3.0f);
#endif

    //�J�����ʒu�̐ݒ�
    m_pCamera->SetPos(CAMPOS_NS);
    //�J�����̒����_�̐ݒ�
    m_pCamera->SetLook(CAMLOOK_NS);

    //----�e�q�[���[�N���X�̏�����----
    //���C
    m_pYui->Initialize();
    //�J�C�g
    m_pKaito->Initialize();

}

//�X�V�֐�
void CNurtureHeroSelectScene::Update()
{
    CSceneManager* SceneMng = &CSceneManager::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

    //�琬�q�[���[BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_NurtureHeroSelect);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_NurtureHeroSelect, 40);

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�L�[�}�l�[�W���̓��쏈��
    CKeyManager::GetInstance().Update();

    //�J�[�\���̈ړ�
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //�I��SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        //�L�[���͂őI����i�߂�
        if (m_SelectNo < CHeroBase::enHeroList::Max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        //�I��SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("�J�������W"),CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), CamLook);
    CCameraManager::GetInstance().SetPos(CamPos);
    CCameraManager::GetInstance().SetLook(CamLook);
#endif

#ifdef DEBUG
    ImGui::Begin(JAPANESE("�I����"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("���C")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("�J�C�g")); }
    ImGui::End();
#endif

    //�V�[���J��
    if (CKeyManager::GetInstance().IsDown(VK_RETURN))
    {
        //����SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }

    //�O�̃V�[���ɖ߂�
    if (CKeyManager::GetInstance().IsDown(VK_ESCAPE))
    {
        //����SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        //�I��ԍ���2�ɂ���
        m_SelectNo = 2;

        //���[�h�I���V�[����
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        switch (m_SelectNo)
        {
        case Yui:
            HeroMng->SelectHero(CHeroManager::Yui);
            break;
        case Kaito:
            HeroMng->SelectHero(CHeroManager::Kaito);
            break;
        default:
            break;
        }
        //�I��ԍ���2�ȊO�Ȃ�
        if (m_SelectNo != 2) 
        {
            SceneMng->LoadCreate(CSceneManager::Nurture);
        }
        else
        {
            //�O�̃V�[����
            SceneMng->LoadCreate(CSceneManager::ModeSelect);
        }
    }
}

//�`��֐�
void CNurtureHeroSelectScene::Draw()
{  
    CHeroManager* Hero = &CHeroManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    WriteText* Text = WriteText::GetInstance();

    //�J�����̓���
    m_pCamera->CameraUpdate();

    SceneMng->GetDx11()->SetDepth(false);
    DrawBasicBackGround();
    SceneMng->GetDx11()->SetDepth(true);

    //�I�𒆃q�[���[�̕`��E�A�j���[�V�����E�J�����z�u
    switch (m_SelectNo)
    {
    case 0:
        //���C
        m_pYui->NurtureHeroSelectAnimation();
        m_pYui->Draw();
        Text->Draw_Text(L"YUI", WriteText::B_Big, HERONAME_POS_NS);
        break;
    case 1:
        //�J�C�g
        m_pKaito->NurtureHeroSelectAnimation();
        m_pKaito->Draw();
        Text->Draw_Text(L"KAITO", WriteText::D_Big, HERONAME_POS_NS);
        break;
    default:
        break;
    }

    //�V�[����,�w���̕`��
    Text->Draw_Text(L"Nurture Hero Select", WriteText::Normal, SCENENAME_POS_NS);    

    //������@�w���o�[�̕`��
    DrawControlBar(true);

    //���̕`��
    DrawArrow();
}

//���̕`��
void CNurtureHeroSelectScene::DrawArrow()
{
    //�ݒ�
    //��
    m_pLeftArrow->SetPosition(ARROW_LEFT_POS_NS);
    m_pLeftArrow->SetScale(ARROW_SCALE);
    m_pLeftArrow->SetRotation(ARROW_LEFT_ROTATE);
    m_pLeftArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pLeftArrow->SetAlpha(ARROW_ALPHA);
    //�E
    m_pRightArrow->SetPosition(ARROW_RIGHT_POS_NS);
    m_pRightArrow->SetScale(ARROW_SCALE);
    m_pRightArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pRightArrow->SetAlpha(ARROW_ALPHA);

    //�`��
    m_pLeftArrow->Draw();
    m_pRightArrow->Draw();
}


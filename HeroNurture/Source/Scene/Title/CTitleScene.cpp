#include "CTitleScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 
#include <cmath>

//�萔�̖��O���
using namespace Constant_TitleScene;

CTitleScene::CTitleScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pYui    ()
    , m_pKaito  ()
    , m_pSky    ()
    , m_pGround ()
    , m_HeroNo  ()
{
    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Create()
{
    //----�X�^�e�B�b�N���b�V��----
    //�X�J�C�{�b�N�X
    m_pSky = std::make_unique<CSky>();
    //�n��
    m_pGround = std::make_unique<CGround>();
    
    //----�X�L�����b�V��----
    //���C
    m_pYui = std::make_unique<CYui>();
    //�J�C�g
    m_pKaito = std::make_unique<CKaito>();

    //----UI----
    //�^�C�g���w�i
    m_pTitleBack = std::make_unique<CUIObject>();
}

void CTitleScene::Releace()
{
    m_pCamera = nullptr;
}

void CTitleScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    //----�X�^�e�B�b�N���b�V��----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //��
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//�n��

    //----�^�C�g����ʂɕ\������q�[���[�̃��b�V���ݒ�----
    m_pYui->LoadMeshData();  //���C
    m_pKaito->LoadMeshData();//�J�C�g

    //----UI----
    m_pTitleBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleBack));
}

void CTitleScene::Initialize()
{
    //�J�����̏����ʒu
    m_pCamera->SetPos(CAM_POS);
    m_pCamera->SetLook(CAM_LOOK);

    //�ǂ���̃q�[���[��\�����邩�A�����Őݒ�
    m_HeroNo = CUtility::GetInstance().GenerateRandomValue(0,1);

    //�ݒ肳�ꂽ�q�[���[�̏�����
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->Initialize();
        m_pYui->SetPosition(YUI_POS);
        m_pYui->SetRotation(YUI_ROT);
        break;
    case 1:
        m_pKaito->Initialize();
        m_pKaito->SetPosition(KAITO_POS);
        m_pKaito->SetRotation(KAITO_ROT);
        break;
    default:
        break;
    }
}

//�X�V�֐�
void CTitleScene::Update()
{   
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = &CKeyManager::GetInstance();

    KeyMng->Update();

    //�^�C�g��BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start,40);

        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        SceneMng->LoadCreate(CSceneManager::Login);
    }

    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start,40);

        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        SceneMng->LoadCreate(CSceneManager::Login);
    }

    #ifdef DEBUG
        //�f�o�b�O����
        Debug();
    #endif
}

void CTitleScene::Draw()
{
    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw();

    //�n�ʂ̕`��
    m_pGround->Draw();

    //�\����؂�ւ���
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->MoveSelectAnim();
        m_pYui->Draw();
        break;
    case 1:
        m_pKaito->MoveSelectAnim();
        m_pKaito->Draw();
        break;
    default:
        break;
    }

    //UI
    DrawUI();
}

void CTitleScene::Debug()
{
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), m_CamLook);
    ImGui::InputFloat3(JAPANESE("�J�C�g���W"), m_KaitoPos);
    ImGui::InputFloat3(JAPANESE("���C���W"),   m_YuiPos);
    ImGui::InputFloat3(JAPANESE("�J�C�g��]"), m_KaitoRot);
    ImGui::InputFloat3(JAPANESE("���C��]"), m_YuiRot);
    //CCameraManager::GetInstance().SetPos(m_CamPos);
    //CCameraManager::GetInstance().SetLook(m_CamLook);
    m_pKaito->SetPosition(m_KaitoPos);
    m_pYui->SetPosition(m_YuiPos);
    m_pKaito->SetRotation(m_KaitoRot);
    m_pYui->SetRotation(m_YuiRot);
    ImGui::End();

}

//�^�C�g����ʂ̕`��
void CTitleScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //�^�C�g��
    Text->Draw_Text(L"HeroNature", WriteText::B_Big, D3DXVECTOR2(TITLE_POS)); 
    //�u�A�J�E���g�쐬�v�e�L�X�g
    Text->Draw_Text(L"�A�J�E���g�쐬", WriteText::Select, D3DXVECTOR2(SELECT_POS));
    //�u���O�C���v�e�L�X�g
    Text->Draw_Text(L"���O�C��", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL));
    //�u�Q�[���I���v�e�L�X�g
    Text->Draw_Text(L"�Q�[���I��", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL*2));
}

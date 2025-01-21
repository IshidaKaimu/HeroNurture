#include "CBattleResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 

CBattleResultScene::CBattleResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pSky()
    , m_pGround()
{
    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CBattleResultScene::~CBattleResultScene()
{
}

void CBattleResultScene::Create()
{
    //----�X�^�e�B�b�N���b�V��----
    //�X�J�C�{�b�N�X
    m_pSky = std::make_unique<CSky>();
    //�n��
    m_pGround = std::make_unique<CGround>();
}

void CBattleResultScene::Releace()
{
    m_pCamera = nullptr;
}

void CBattleResultScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    //----�X�^�e�B�b�N���b�V��----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //��
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//�n��
}

void CBattleResultScene::Initialize()
{
    //�J�����̏����ʒu
    m_pCamera->SetPos(5.0f, 4.0f, -5.0f);
    m_pCamera->SetLook(0.0f, 4.0f, 0.0f);
}

//�X�V�֐�
void CBattleResultScene::Update()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    KeyMng->Update();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

void CBattleResultScene::Draw()
{
    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw();

    //�n�ʂ̕`��
    m_pGround->Draw();

    //UI
    DrawUI();
}

//�^�C�g����ʂ̕`��
void CBattleResultScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        Text->Draw_Text(L"WIN", WriteText::Success, RESULTTEXT_POS);
        break;
    case CSceneManager::Lose:
        Text->Draw_Text(L"LOSE", WriteText::Failure, RESULTTEXT_POS);
        break;
    default:
        break;
    }  
}


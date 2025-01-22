#include "CBattleResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
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
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();


    //----�X�^�e�B�b�N���b�V��----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //��
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//�n��

    //----�X�L�����b�V��----
    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:    
        HeroMng->LoadMeshData();
        break;
    case CSceneManager::Lose:
        EnemyHeroMng->LoadMeshData();
        break;
    default:
        break;
    }
}

void CBattleResultScene::Initialize()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

    //�J�����̏����ʒu

    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        m_pCamera->SetPos(-2.4f, 2.0f, 1.1f);
        m_pCamera->SetLook(-5.0f, 2.0f, -1.0f);
        HeroMng->Initialize();
        break;
    case CSceneManager::Lose:
        m_pCamera->SetPos(-0.3f, 1.8f, 1.8f);
        m_pCamera->SetLook(2.0f, 2.0f, 1.0f);
        EnemyHeroMng->Initialize();
        break;
    default:
        break;
    }

}

//�X�V�֐�
void CBattleResultScene::Update()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    KeyMng->Update();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Battle);


    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        //������BGM�̍Đ�
        CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Win);
        CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Win, 40);
        break;
    case CSceneManager::Lose:
        //�s�k��BGM�̍Đ�
        CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Lose);
        CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Lose, 40);
        break;
    default:
        break;
    }


    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //����SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

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
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw();

    //�n�ʂ̕`��
    m_pGround->Draw();


    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        HeroMng->MoveSelectAnim();
        HeroMng->Draw();
        break;
    case CSceneManager::Lose:
        EnemyHeroMng->MoveSelectAnim();
        EnemyHeroMng->Draw();
        break;
    default:
        break;
    }


    //UI
    DrawUI();

    //�f�o�b�O
    Debug();
}

void CBattleResultScene::Debug()
{
#if DEBUG
    ImGui::Begin(JAPANESE("�J�����ʒu"));
    ImGui::Text(JAPANESE("���WX:%f\n���WY:%f\n���WZ:%f"), m_pCamera->GetPos().x,m_pCamera->GetPos().y,m_pCamera->GetPos().z);
    ImGui::InputFloat3(JAPANESE("�����_:%f"), m_CamLook);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

}

//�^�C�g����ʂ̕`��
void CBattleResultScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        Text->Draw_Text(L"WIN", WriteText::Win, RESULTTEXT_POS);
        break;
    case CSceneManager::Lose:
        Text->Draw_Text(L"LOSE", WriteText::Lose, RESULTTEXT_POS);
        break;
    default:
        break;
    }  
}


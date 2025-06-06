#include "CBattleResultScene.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Battle\CBattleManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"	
#include "KeyManager\CKeyManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 

//�萔�̖��O���
using namespace Constant_BattleResultScene;


CBattleResultScene::CBattleResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
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
    //�n��
    m_pGround = std::make_unique<CGround>();
    //----------------------------
}

void CBattleResultScene::Releace()
{
    m_pCamera = nullptr;
}

void CBattleResultScene::LoadData()
{
    CSceneManager*     SceneMng     = &CSceneManager::GetInstance();
    CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();
    CBattleManager*    BattleMng    = &CBattleManager::GetInstance();

    //----�X�^�e�B�b�N���b�V��----
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//�n��
    //----------------------------

    //----�X�L�����b�V��----
    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:    
        HeroMng->LoadMeshData();
        break;
    case BattleMng->Lose:
        EnemyHeroMng->LoadMeshData();
        break;
    default:
        break;
    }
    //---------------------
}

void CBattleResultScene::Initialize()
{
    CSceneManager* SceneMng         = &CSceneManager::GetInstance();
    CHeroManager* HeroMng           = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();
    CBattleManager* BattleMng       = &CBattleManager::GetInstance();


    //�J�����̏����ʒu
    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        m_pCamera->SetPos(WIN_CAM_POS);
        m_pCamera->SetLook(WIN_CAM_LOOK);
        HeroMng->Initialize();
        break;
    case BattleMng->Lose:
        m_pCamera->SetPos(LOSE_CAM_POS);
        m_pCamera->SetLook(LOSE_CAM_LOOK);
        EnemyHeroMng->Initialize();
        break;
    default:
        break;
    }
}

//�X�V�֐�
void CBattleResultScene::Update()
{
    CSceneManager* SceneMng   = &CSceneManager::GetInstance();
    CKeyManager* KeyMng       = &CKeyManager::GetInstance();
    CBattleManager* BattleMng = &CBattleManager::GetInstance();

    KeyMng->Update();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Battle);

    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        //������BGM�̍Đ�
        CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Win);
        CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Win, 40);
        break;
    case BattleMng->Lose:
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
    CSceneManager* SceneMng         = &CSceneManager::GetInstance();
    CHeroManager* HeroMng           = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();
    CBattleManager* BattleMng       = &CBattleManager::GetInstance();

    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�n�ʂ̕`��
    m_pGround->Draw();

    //��̕`��
    DrawSky();

    //���s�ɉ����ĕ`���ς���
    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        HeroMng->MoveSelectAnim();
        HeroMng->Draw();
        break;
    case BattleMng->Lose:
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
    WriteText* Text           = WriteText::GetInstance();
    CSceneManager* SceneMng   = &CSceneManager::GetInstance();
    CBattleManager* BattleMng = &CBattleManager::GetInstance();

    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        Text->Draw_Text(L"WIN", WriteText::Win,RESULTTEXT_POS);
        break;
    case BattleMng->Lose:
        Text->Draw_Text(L"LOSE", WriteText::Lose,RESULTTEXT_POS);
        break;
    default:
        break;
    }  
}


#include "CModeSelectScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 
//�萔�̖��O���
using namespace Constant_ModeSelectScene;

CModeSelectScene::CModeSelectScene()
{
    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CModeSelectScene::~CModeSelectScene()
{
}

void CModeSelectScene::Create()
{
    //----UI----
    m_pNatureMode = std::make_unique<CUIObject>(); //�琬���[�h
    m_pBattleMode = std::make_unique<CUIObject>(); //�o�g�����[�h
    m_pCover      = std::make_unique<CUIObject>(); //�J�o�[
}

void CModeSelectScene::Releace()
{
}

void CModeSelectScene::LoadData()
{   
    //----UI----
    m_pNatureMode->AttachSprite(CUIManager::GetSprite(CUIManager::ModeSelectLeft));
    m_pBattleMode->AttachSprite(CUIManager::GetSprite(CUIManager::ModeSelectRight));
    m_pCover->AttachSprite(CUIManager::GetSprite(CUIManager::ModeSelectCover));
}

void CModeSelectScene::Initialize()
{
}

//�X�V�֐�
void CModeSelectScene::Update()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�^�C�g��BGM�A�퓬����BGM�̒�~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_NatureResult);
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Win);
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Lose);

    //���[�h�I��BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_ModeSelect);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_ModeSelect, 40);


    //�L�[�}�l�[�W���[�̍X�V
    KeyMng->Update();

    //�J�[�\���̈ړ�
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //�I��SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        //�L�[���͂őI����i�߂�
        if (m_SelectNo < enModeList::Max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        //�I��SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = enModeList::Max-1; }
    }



    //�V�[���J��(��)
    if (CKeyManager::GetInstance().IsDown(VK_RETURN))
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
        switch (m_SelectNo)
        {
        case 0:
            SceneMng->LoadCreate(CSceneManager::NatureHeroSelect);           //�琬���[�h
            break;
        case 1:
            SceneMng->LoadCreate(CSceneManager::BattleHeroSelect); //�o�g�����[�h
            break;
        default:
            break;
        }
    }
}

void CModeSelectScene::Draw()
{
    //UI�̕`��
    DrawUI();
}

//���[�h�I����ʂ̕`��
void CModeSelectScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //----�eUI�̐ݒ�----
    //�琬���[�h
    m_pNatureMode->SetPosition(NATUREMODE_POS);         //�ʒu
    m_pNatureMode->SetScale(MODE_SCALE);                //�g�k
    m_pNatureMode->SetDisplay(MODE_DISP.x,MODE_DISP.y); //��
    m_pNatureMode->SetAlpha(MODE_ALPHA);                //���l
    //�o�g�����[�h
    m_pBattleMode->SetPosition(BATTLEMODE_POS);         //�ʒu
    m_pBattleMode->SetScale(MODE_SCALE);                //�g�k
    m_pBattleMode->SetDisplay(MODE_DISP.x,MODE_DISP.y); //��
    m_pBattleMode->SetAlpha(MODE_ALPHA);                //���l

    //�I������Ă��Ȃ����ɔ킹��摜
    //�ʒu
    switch (m_SelectNo)
    {
    case 0:
        m_pCover->SetPosition(BATTLEMODE_POS);
        break;
    case 1:
        m_pCover->SetPosition(NATUREMODE_POS);
        break;
    default:
        break;
    }

    m_pCover->SetScale(MODE_SCALE);               //�g�k
    m_pCover->SetDisplay(MODE_DISP.x,MODE_DISP.y);//��
    m_pCover->SetAlpha(COVER_ALPHA);              //���l

    CSceneManager::GetInstance()->GetDx11()->SetDepth(false);
    //�琬���[�h�`��
    m_pNatureMode->Draw();
    //�o�g�����[�h�`��
    m_pBattleMode->Draw();
    //�I������Ă��Ȃ����ɔ킹��摜
    m_pCover->Draw();
    //�V�[�����̕`��
    Text->Draw_Text(L"MODE SELECT", WriteText::Normal, SCENENAME_POS);
    CSceneManager::GetInstance()->GetDx11()->SetDepth(true);
}

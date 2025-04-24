#include "Scene\NatureResult\CNatureResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Rank\CRank.h"
#include <cmath>
#include <fstream>
#include <sstream>

//�萔�̖��O���
using namespace Constant_NatureResultScene;

CNatureResultScene::CNatureResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pParamList  ()
    , m_pJson       ()
    , m_ResultWriter()
{
}

CNatureResultScene::~CNatureResultScene()
{
}

//�\�z�֐�
void CNatureResultScene::Create()
{
    //�p�����[�^�w�iUI�̃C���X�^���X����
    m_pParamList = std::make_unique<CUIObject>();
}

//�f�[�^�ݒ�֐�
void CNatureResultScene::LoadData()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�Z�b�g���ꂽ�q�[���[�̃��b�V���ݒ�
    HeroMng->LoadMeshData();

    //�p�����[�^�̔w�i�̃X�v���C�g�ݒ�
    m_pParamList->AttachSprite(CUIManager::GetSprite(CUIManager::ResultParamList));
}

//�j���֐�
void CNatureResultScene::Releace()
{
}

//�������֐�
void CNatureResultScene::Initialize()
{
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�Z�b�g����Ă���q�[���[�̏�����
    Hero->Initialize();

    //�p�����[�^�w�iUI���̏�����
    m_pParamList->SetPosition(PARAMBACK_POS);
    m_pParamList->SetScale(PARAMBACK_SCALE);
    m_pParamList->SetAlpha(1.0f);
    m_pParamList->SetDisplay(1.0f,1.0f);

    //�J�����ʒu�̐ݒ�
    m_pCamera->SetPos(CAMPOS);
    //�J���������_�̐ݒ�
    m_pCamera->SetLook(CAMLOOK);
}

//�X�V�֐�
void CNatureResultScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Nature);


    //�琬����BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_NatureResult);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_NatureResult, 40);


    //�L�[�}�l�[�W���̓��쏈��
    KeyMng->Update();

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
        CSceneManager::GetInstance()->SetIsDataLoaded(false);
        m_pJson->SaveResult(HeroMng->GetHeroName(), m_ResultWriter);
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::ModeSelect);
    }
}

//�`��֐�
void CNatureResultScene::Draw()
{
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̕`��
    Hero->Draw();

    //�琬���ʂ̕`��
    DrawResult();

    //�f�o�b�O����
    Debug();
}

//�f�o�b�O����
void CNatureResultScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif
}

//�琬���ʂ̕`��
void CNatureResultScene::DrawResult()
{
    WriteText* Text = WriteText::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�u�琬�����N�v�e�L�X�g�̕`��
    std::wstring ResultText = L"�琬�����N";
    Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS, false, true);

    //�p�����[�^�̔w�i�̕`��
    m_pParamList->Draw();

    //�e�p�����[�^�̒l�A�����N�̕`��
    DrawParamUI(HeroMng->GetParam().Power, 0);
    DrawParamUI(HeroMng->GetParam().Magic, 1);
    DrawParamUI(HeroMng->GetParam().Speed, 2);
    DrawParamUI(HeroMng->GetParam().Hp, 3);

    //�����N�̕`��
    CRank::GetInstance().DrawRank(ParamTotal(), 1, RANK_POS);
}

//�p�����[�^�̍��v�l
float CNatureResultScene::ParamTotal()
{
    //�Z�b�g���̃q�[���[�̃X�e�[�^�X��ϐ��ɑ��
    CHeroManager::enParam HeroParam = CHeroManager::GetInstance().GetParam();

    //�X�e�[�^�X�̍��v���v�Z�A���
    float Total = HeroParam.Power + HeroParam.Magic + HeroParam.Speed + HeroParam.Hp;

    return Total;
}

//�p�����[�^UI�̕`��
void CNatureResultScene::DrawParamUI(float paramvalue, int no)
{
    WriteText* Text = WriteText::GetInstance();
    CRank* Rank = &CRank::GetInstance();

    //----�e�p�����[�^��UI�̕`��(�w�i,�l,�����N)----
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POS.x, PARAMVALUE_POS.y + (PARAMVALUE_INTERVAL* no)));
    Rank->DrawRank(paramvalue, 2, D3DXVECTOR2(PARAMRANK_POS.x, PARAMRANK_POS.y + (PARAMRANK_INTERVAL * no)));
}

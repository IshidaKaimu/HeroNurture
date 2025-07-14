#include "Scene\NurtureResult\CNurtureResultScene.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"
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
using namespace Constant_NurtureResultScene;

CNurtureResultScene::CNurtureResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pParamList  ()
    , m_pJson       ()
    , m_ResultWriter()
{
}

CNurtureResultScene::~CNurtureResultScene()
{
}

//�\�z�֐�
void CNurtureResultScene::Create()
{
    //�p�����[�^�w�iUI�̃C���X�^���X����
    m_pParamList = std::make_unique<CUIObject>();
}

//�f�[�^�ݒ�֐�
void CNurtureResultScene::LoadData()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�Z�b�g���ꂽ�q�[���[�̃��b�V���ݒ�
    HeroMng->LoadMeshData();

    //�p�����[�^�̔w�i�̃X�v���C�g�ݒ�
    m_pParamList->AttachSprite(CUIManager::GetSprite(CUIManager::ResultParamList));
}

//�j���֐�
void CNurtureResultScene::Releace()
{
}

//�������֐�
void CNurtureResultScene::Initialize()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�Z�b�g����Ă���q�[���[�̏�����
    HeroMng->Initialize();

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
void CNurtureResultScene::Update()
{
    CKeyManager*     KeyMng     = &CKeyManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Nurture);

    //�琬����BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_NurtureResult);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_NurtureResult, BGM_VOLUME);


    //�L�[�}�l�[�W���̓��쏈��
    KeyMng->Update();

    //�V�[���J��(��)
    if (CKeyManager::GetInstance().IsDown(VK_RETURN))
    {
        //����SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, SE_VOLUME);

        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        NurtureMng->SetIsDataLoaded(false);
        m_pJson->SaveResult(HeroMng->GetSelectHeroName(), m_ResultWriter);
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

//�`��֐�
void CNurtureResultScene::Draw()
{
    WriteText*    Text = WriteText::GetInstance();
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�J�����̓���
    m_pCamera->CameraUpdate();


    CSceneManager::GetInstance().GetDx11()->SetDepth(false);

    //�ėp�w�i�̕`��
    DrawBasicBackGround();

    //�琬���ʂ̕`��
    DrawResult();

    CSceneManager::GetInstance().GetDx11()->SetDepth(true);

    //�Z�b�g���ꂽ�q�[���[�̕`��
    Hero->Draw();

    //������@�w���o�[�̕`��
    DrawControlBar(false);
    //������@�w���uEnter ���[�h�I���ցv�e�L�X�g�̕`��
    Text->Draw_Text(L"Enter ���[�h�I����", WriteText::Control, ENTERTEXT_POS);

    //�f�o�b�O����
    Debug();
}

//�f�o�b�O����
void CNurtureResultScene::Debug()
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
void CNurtureResultScene::DrawResult()
{
    WriteText*    Text    = WriteText::GetInstance();
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
float CNurtureResultScene::ParamTotal()
{
    //�Z�b�g���̃q�[���[�̃X�e�[�^�X��ϐ��ɑ��
    CHeroManager::enParam HeroParam = CHeroManager::GetInstance().GetParam();

    //�X�e�[�^�X�̍��v���v�Z�A���
    float Total = HeroParam.Power + HeroParam.Magic + HeroParam.Speed + HeroParam.Hp;

    return Total;
}

//�p�����[�^UI�̕`��
void CNurtureResultScene::DrawParamUI(float paramvalue, int no)
{
    WriteText* Text    = WriteText::GetInstance();
    CRank*     Rank    = &CRank::GetInstance();
    CUtility*  Utility = &CUtility::GetInstance();

    //----�e�p�����[�^��UI�̕`��(�w�i,�l,�����N)----
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, Utility->PosCorrection(static_cast<int>(paramvalue),3,D3DXVECTOR2(PARAMVALUE_POS.x, PARAMVALUE_POS.y + (PARAMVALUE_INTERVAL* no))));
    Rank->DrawRank(paramvalue, 2, D3DXVECTOR2(PARAMRANK_POS.x, PARAMRANK_POS.y + (PARAMRANK_INTERVAL * no)));
}

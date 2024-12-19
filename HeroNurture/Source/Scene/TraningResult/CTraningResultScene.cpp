#include "Scene\TraningResult\CTraningResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include <cmath>
#include <fstream>
#include <sstream>


CTraningResultScene::CTraningResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pPowerParam()
    , m_pMagicParam()
    , m_pSpeedParam()
    , m_pHpParam   ()
{
}

CTraningResultScene::~CTraningResultScene()
{
}

//�\�z�֐�
void CTraningResultScene::Create()
{
    //�e�p�����[�^�w�iUI�̃C���X�^���X����
    m_pPowerParam = std::make_unique<CUIObject>();
    m_pMagicParam = std::make_unique<CUIObject>();
    m_pSpeedParam = std::make_unique<CUIObject>();
    m_pHpParam    = std::make_unique<CUIObject>();
}

//�f�[�^�ݒ�֐�
void CTraningResultScene::LoadData()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�q�[���[�}�l�[�W���[
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�Z�b�g���ꂽ�q�[���[�̃��b�V���ݒ�
    Hero->LoadMeshData();

    //----�e�p�����[�^��UI�̃X�v���C�g�ݒ�----
    //�ؗ�
    //m_pPowerParam->AttachSprite(CUIManager::GetSprite(CUIManager::PowerParam));
    ////����
    //m_pMagicParam->AttachSprite(CUIManager::GetSprite(CUIManager::MagicParam));
    ////�f����
    //m_pSpeedParam->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedParam));
    ////�̗�
    //m_pHpParam->AttachSprite(CUIManager::GetSprite(CUIManager::HpParam));

}

//�j���֐�
void CTraningResultScene::Releace()
{
}

//�������֐�
void CTraningResultScene::Initialize()
{
    //�q�[���[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�Z�b�g����Ă���q�[���[�̏�����
    Hero->Initialize();

    //�e�p�����[�^�w�iUI�̏�����
    ParamBackUIInit(m_pPowerParam,1);
    ParamBackUIInit(m_pMagicParam,2);
    ParamBackUIInit(m_pSpeedParam,3);
    ParamBackUIInit(m_pHpParam,4);

    //�J�����ʒu�̐ݒ�
    m_pCamera->SetPos(RESULT_CAMPOS);
    //�J���������_�̐ݒ�
    m_pCamera->SetLook(RESULT_CAMLOOK);
}

//�X�V�֐�
void CTraningResultScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�L�[�}�l�[�W���[
    CKeyManager* KeyMng = CKeyManager::GetInstance();
    //�q�[���[�}�l�[�W���[
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�L�[�}�l�[�W���̓��쏈��
    KeyMng->Update();

    //�J�[�\���̈ړ�
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //�L�[���͂őI����i�߂�
        if (m_SelectNo < CHeroBase::enCharacterList::max - 1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::HeroSelect);
    }
}

//�`��֐�
void CTraningResultScene::Draw()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�q�[���[�}�l�[�W���[
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
void CTraningResultScene::Debug()
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
void CTraningResultScene::DrawResult()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�u�ŏI�]���v�e�L�X�g
    std::wstring ResultText = L"�ŏI�]��";

    Text->Draw_Text(ResultText, WriteText::Normal, D3DXVECTOR2(900.0f, 0.0f), false, true);

    //----�e�p�����[�^��UI�̕`��----
    //�ؗ�
    DrawParamUI(m_pPowerParam,HeroMng->GetParam().Power,1);
    //����
    DrawParamUI(m_pMagicParam,HeroMng->GetParam().Magic,2);
    //�f����
    DrawParamUI(m_pSpeedParam,HeroMng->GetParam().Speed,3);
    //�̗�
    DrawParamUI(m_pHpParam,HeroMng->GetParam().Hp,4);

    //�����N�̕`��
    CUtility::GetInstance().DrawRank(ParamTotal(), 1, RANK_POSX, RANK_POSY);
}

//�p�����[�^�̍��v�l
float CTraningResultScene::ParamTotal()
{
    //�Z�b�g���̃q�[���[�̃X�e�[�^�X��ϐ��ɑ��
    CHeroManager::enParam HeroParam = CHeroManager::GetInstance().GetParam();

    //�X�e�[�^�X�̍��v���v�Z�A���
    float Total = HeroParam.Power + HeroParam.Magic + HeroParam.Speed + HeroParam.Hp;

    return Total;
}

//�p�����[�^UI�̏����ݒ�
void CTraningResultScene::ParamBackUIInit(std::unique_ptr<CUIObject>& param, int no)
{
    //�ʒu
    param->SetPosition(PARAMBACK_POSX, PARAMBACK_POSY * no/4, 0.0f);
    //�g�k
    param->SetScale(PARAMBACK_SCALE);
    //���l
    param->SetAlpha(1.0f);
    //���A����
    param->SetDisplay(1.0f, 1.0f);
}

//�p�����[�^UI�̕`��
void CTraningResultScene::DrawParamUI(std::unique_ptr<CUIObject>& param, float paramvalue, int no)
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�ėp�N���X
    CUtility* Utility = &CUtility::GetInstance();

    //----�e�p�����[�^��UI�̕`��(�w�i,�l,�����N)----
    param->Draw();
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, D3DXVECTOR2(0.0f, 200.0f * no));
    Utility->DrawRank(paramvalue, 2,PARAMBACK_POSX,PARAMBACK_POSY * no/4);
}


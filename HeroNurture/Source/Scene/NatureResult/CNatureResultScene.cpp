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
#include <cmath>
#include <fstream>
#include <sstream>


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
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�q�[���[�}�l�[�W���[
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    //UI�}�l�[�W���[
    CUIManager* UIMng = CUIManager::GetInstance();

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
    //�q�[���[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�Z�b�g����Ă���q�[���[�̏�����
    Hero->Initialize();

    //�p�����[�^�w�iUI���̏�����
    m_pParamList->SetPosition(PARAMBACK_POSX_NR,PARAMBACK_POSY_NR,0.0);
    m_pParamList->SetScale(PARAMBACK_SCALE_NR);
    m_pParamList->SetAlpha(1.0f);
    m_pParamList->SetDisplay(1.0f,1.0f);

    //�J�����ʒu�̐ݒ�
    m_pCamera->SetPos(CAMPOS_NR);
    //�J���������_�̐ݒ�
    m_pCamera->SetLook(CAMLOOK_NR);
}

//�X�V�֐�
void CNatureResultScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�L�[�}�l�[�W���[
    CKeyManager* KeyMng = CKeyManager::GetInstance();
    //�q�[���[�}�l�[�W���[
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�L�[�}�l�[�W���̓��쏈��
    KeyMng->Update();

    //�琬���ʂ�ۑ�����t�@�C���̊K�w
    std::string SaveHierarchy = "Data\\Hero\\Result\\";

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
        CSceneManager::GetInstance()->SetIsDataLoaded(false);
        m_pJson->SaveResult(HeroMng->GetHeroName(), m_ResultWriter, SaveHierarchy);
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::HeroSelect);
    }
}

//�`��֐�
void CNatureResultScene::Draw()
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
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�u�琬�����N�v�e�L�X�g�̕`��
    std::wstring ResultText = L"�琬�����N";
    Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS_NR, false, true);

    //�p�����[�^�̔w�i�̕`��
    m_pParamList->Draw();

    //�e�p�����[�^�̒l�A�����N�̕`��
    DrawParamUI(HeroMng->GetParam().Power, 0);
    DrawParamUI(HeroMng->GetParam().Magic, 1);
    DrawParamUI(HeroMng->GetParam().Speed, 2);
    DrawParamUI(HeroMng->GetParam().Hp, 3);


    //�����N�̕`��
    CUtility::GetInstance().DrawRank(ParamTotal(), 1, RANK_POSX_NR, RANK_POSY_NR);
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
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�ėp�N���X
    CUtility* Utility = &CUtility::GetInstance();

    //----�e�p�����[�^��UI�̕`��(�w�i,�l,�����N)----
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_NR, PARAMVALUE_POSY_NR + (PARAMVALUE_INTERVAL_NR* no)));
    Utility->DrawRank(paramvalue, 2, PARAMRANK_POSX_NR, PARAMRANK_POSY_NR + (PARAMRANK_INTERVAL_NR * no));
}

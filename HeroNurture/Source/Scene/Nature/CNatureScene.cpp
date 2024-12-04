#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"


CNatureScene::CNatureScene()
    : m_pCamera  ( &CCameraManager::GetInstance() )
    , m_pHero    ( &CHeroManager::GetInstance() )
    , m_pJson    ()
    , m_Name     ()
    , m_pGround  ()
    , m_pSky     ()
    , m_ParamData()
{
}

CNatureScene::~CNatureScene()
{
}

//�\�z�֐�
void CNatureScene::Create()
{
    //----�C���X�^���X����----
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃C���X�^���X����
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        m_pHero->SetHero(CHeroManager::Yui);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        m_pHero->SetHero(CHeroManager::Kaito);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //�X�^�e�B�b�N���b�V���I�u�W�F�N�g
    //�n��
    m_pGround = std::make_unique<CGround>();
    //�X�J�C�{�b�N�X
    m_pSky    = std::make_unique<CSky>();

    //UI�I�u�W�F�N�g
    //�e��p�����[�^
    //�ؗ�
    m_pPowerParam = new CUIObject();
    //����
    m_pMagicParam = new CUIObject();
    //�f����
    m_pSpeedParam = new CUIObject();
    //�̗�
    m_pHpParam    = new CUIObject();
}

//�j���֐�
void CNatureScene::Releace()
{
    //----�j��----
    //�J����
    m_pCamera = nullptr;
    //�q�[���[�}�l�[�W���[
    m_pHero   = nullptr;
}


//�f�[�^�ǂݍ��݊֐�
void CNatureScene::LoadData()
{   
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃��b�V���f�[�^�̓ǂݍ���
    CHeroManager::GetInstance().LoadMeshData();

    CHeroManager::GetInstance().LoadParamData(m_ParamData);

    //�n��
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));

    //�e�p�����[�^��UI�̃X�v���C�g�ݒ�
    //�ؗ�
    m_pPowerParam->AttachSprite(CUIManager::GetSprite(CUIManager::PowerParam));
    //����
    m_pMagicParam->AttachSprite(CUIManager::GetSprite(CUIManager::MagicParam));
    //�f����
    m_pSpeedParam->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedParam));
    //�̗�
    m_pHpParam->AttachSprite(CUIManager::GetSprite(CUIManager::HpParam));
}

//�������֐�
void CNatureScene::Initialize()
{
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̏�����
    m_pHero->Initialize();

    //�e�q�[���[�̃J�����ʒu�A�J�����̒����_�̐ݒ�
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        m_pCamera->SetPos (CAMERAPOS_YUI);
        m_pCamera->SetLook(CAMERALOOK_YUI);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        m_pCamera->SetPos (CAMERAPOS_KAITO);
        m_pCamera->SetLook(CAMERALOOK_KAITO);
        break;
    default:
        break;
    }

    //----���C�g���----
    //�ʒu
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //����
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
   
    //----�e��p�����[�^UI�̏����ݒ�----
    //�ؗ�
    ParamInit(m_pPowerParam, 1);
    //����
    ParamInit(m_pMagicParam, 2);
    //�f����
    ParamInit(m_pSpeedParam, 3);
    //�̗�
    ParamInit(m_pHpParam, 4);

}


//�X�V�֐�
void CNatureScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̍X�V
    m_pHero->Update();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃A�j���[�V����
    m_pHero->Animation();

    //�L�[�}�l�[�W���[�̍X�V����
    CKeyManager::GetInstance()->Update();

    //�X�e�[�^�X�㏸����
    if (CKeyManager::GetInstance()->IsDown('P'))
    {
        m_SceneTransitionFlg = true;
    }
    if (m_SceneTransitionFlg && FadeOut())
    {
        m_pHero->PowerUp(30);
        //�q�[���[���Ƃ̃p�����[�^���̏�������
        switch (m_pHero->GetSelectHero())
        {
        case CHeroManager::Yui:
            //���C
            WriteParam("Yui");
            break;
        case CHeroManager::Kaito:
            //�J�C�g
            WriteParam("Kaito");
            break;
        default:
            break;
        }
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::Training);
    }

#ifdef DEBUG 
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"),m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"),m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef _DEBUG 

    ImGui::Begin(JAPANESE("�p�����[�^"));
    ImGui::Text(JAPANESE("�ؗ�:%d"),   m_pHero->GetParam().Power);
    ImGui::Text(JAPANESE("����:%d"),   m_pHero->GetParam().Magic);
    ImGui::Text(JAPANESE("�f����:%d"), m_pHero->GetParam().Speed);
    ImGui::Text(JAPANESE("�̗�:%d"),   m_pHero->GetParam().Hp);
    ImGui::End();

#endif


}

//�`��֐�
void CNatureScene::Draw()
{
    //�J�����̍X�V����
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̕`��
    CHeroManager::GetInstance().Draw();

    //�n�ʃN���X�̕`��
    m_pGround->Draw();

    //�c��^�[�����̕`��
    DrawRemainingTurn();

    //�e�p�����[�^UI�̕`��
    DrawParam();
}

//�e�q�[���[�̃f�[�^�ǂݍ���
void CNatureScene::LoadHeroData( const std::string& heroname )
{
    //�ǂݍ��ރt�@�C���̃p�X
    //����̓ǂݍ��ݎ��ɓǂݍ��ޏ����X�e�[�^�X�t�@�C��
    std::string InitFilePath = "Data\\Hero\\HeroData";
    //�p�����[�^���X�V���ɓǂݍ��ރt�@�C��
    std::string ParamFilePath = "Data\\Hero\\Paramater\\" + heroname;

    //json�ɕۑ����ꂽ�f�[�^�̓ǂݍ���
    //�ǂݍ��݉񐔂ɉ����ēǂݍ��ރt�@�C����ς���
    if (!CSceneManager::GetInstance()->GetIsDataLoaded()) 
    {
        //����̓ǂݍ��ݎ�
        if (!m_pJson->Load(m_ParamData, InitFilePath)) { return; }
    }
    else
    {
        //2�x�ڈȍ~�̓ǂݍ��ݎ�
        if (!m_pJson->Load(m_ParamData, ParamFilePath)) { return; }
    }
}

//�p�����[�^���̏�������
void CNatureScene::WriteParam( const std::string& heroname )
{
    //�������ޏ��̊i�[
    m_ParamWriter["Name"] = heroname;
    m_ParamWriter["Paramater"]["Power"] = m_pHero->GetParam().Power;
    m_ParamWriter["Paramater"]["Magic"] = m_pHero->GetParam().Magic;
    m_ParamWriter["Paramater"]["Speed"] = m_pHero->GetParam().Speed;
    m_ParamWriter["Paramater"]["Hp"] = m_pHero->GetParam().Hp;

    //�t�@�C���ɏ�������
    m_pJson->CreateOrWrite( "Data\\Hero\\Paramater\\",m_ParamWriter);
}


//�e��p�����[�^�ݒ�
void CNatureScene::ParamInit(CUIObject* param, int no)
{
    //�ʒu
    param->SetPosition(PARAM_POSX * no, PARAM_POSY, 0.0f);
    //�g�k
    param->SetScale(0.3f, 0.3f, 0.3f);
    //���l
    param->SetAlpha(1.0f);
}

//�e��p�����[�^�̕`��
void CNatureScene::DrawParam()
{
    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();
    //----�e��p�����[�^��UI�`��----
    //�ؗ�
    m_pPowerParam->Draw();
    Text->Draw_Text(std::to_wstring(m_pHero->GetParam().Power), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 1.0f, PARAM_POSY));
    //����
    m_pMagicParam->Draw();
    Text->Draw_Text(std::to_wstring(m_pHero->GetParam().Magic), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 2.0f, PARAM_POSY));
    //�f����
    m_pSpeedParam->Draw();
    Text->Draw_Text(std::to_wstring(m_pHero->GetParam().Speed), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 3.0f, PARAM_POSY));
    //�̗�
    m_pHpParam->Draw();
    Text->Draw_Text(std::to_wstring(m_pHero->GetParam().Hp), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 4.0f, PARAM_POSY));
}

//�c��^�[�����̕`��
void CNatureScene::DrawRemainingTurn()
{
    //������wstring�^�ɕϊ�
    std::wstring Turn = std::to_wstring(CSceneManager::GetInstance()->GetRemainingTurn());

    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();

    //�c��^�[�����̕`��
    Text->Draw_Text(L"�c��", WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn, WriteText::Turn, D3DXVECTOR2(110.0, -30.0));
    Text->Draw_Text(L"�^�[��", WriteText::Normal, D3DXVECTOR2(160.0, -20.0));
}

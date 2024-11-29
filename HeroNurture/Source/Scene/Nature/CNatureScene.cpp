#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"


CNatureScene::CNatureScene()
    : m_pCamera  ( &CCameraManager::GetInstance() )
    , m_pHero    ( &CHeroManager::GetInstance() )
    , m_pJson    ()
    , m_Name     ()
    , m_pGround  ()
    , m_pSky     ()
    , m_CharaData()
    , m_ParamData()
    , m_Turn     ()
{
}

CNatureScene::~CNatureScene()
{
}

//�\�z�֐�
void CNatureScene::Create()
{
    //----�C���X�^���X����----
 
    //----�Z�b�g���ꂽ�q�[���[�̃N���X�̃C���X�^���X����----
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        m_pHero->SetHero(CHeroManager::Yui);
        //�t�@�C���̍쐬�A�ǂݍ���
        CreateHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        m_pHero->SetHero(CHeroManager::Kaito);
        //�t�@�C���̍쐬�A�ǂݍ���
        CreateHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //----�X�^�e�B�b�N���b�V��----
    //�n��
    m_pGround = std::make_unique<CGround>();
    //�X�J�C�{�b�N�X
    m_pSky    = std::make_unique<CSky>();

    //----UI----
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
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃f�[�^�ǂݍ���
    CHeroManager::GetInstance().LoadData(m_ParamData);

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

    //�琬�c��^�[�����̏�����
    m_Turn = MAX_TURN;

    //----�e��p�����[�^��UI�̐ݒ�----
    //�ؗ�
    m_pPowerParam->SetPosition(300.0f,300.0f,0.0f);
    m_pPowerParam->SetScale(1.0f,1.0f,1.0f);
    m_pPowerParam->SetAlpha(1.0f);

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
    ImGui::Text(JAPANESE("�ؗ�:%d"), m_pHero->GetStatus().Power);
    ImGui::Text(JAPANESE("����:%d"), m_pHero->GetStatus().Magic);
    ImGui::Text(JAPANESE("�f����:%d"), m_pHero->GetStatus().Speed);
    ImGui::Text(JAPANESE("�̗�:%d"), m_pHero->GetStatus().Hp);
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
void CNatureScene::CreateHeroData( const std::string& heroname )
{
    //�t�@�C�����ƊK�w������
    std::string FilePath = "Data\\Hero\\HeroData";

    //json�ɕۑ����ꂽ�f�[�^�̓ǂݍ���
    if (!m_pJson->Load(m_ParamData, FilePath))
    {
        return;
    }
}

//�c��^�[�����̕`��
void CNatureScene::DrawRemainingTurn()
{
    //������wstring�^�ɕϊ�
    std::wstring Turn = std::to_wstring(m_Turn);

    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text =  WriteText::GetInstance();

    //�c��^�[�����̕`��
    Text->Draw_Text(L"�c��",WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn,WriteText::Turn, D3DXVECTOR2(110.0, -30.0));
    Text->Draw_Text(L"�^�[��",WriteText::Normal, D3DXVECTOR2(160.0, -20.0));
}

//�e��p�����[�^�̕`��
void CNatureScene::DrawParam()
{
    //----�e��p�����[�^��UI�`��----
    //�ؗ�
    m_pPowerParam->Draw();
    //����
    m_pMagicParam->Draw();
    //�f����
    m_pSpeedParam->Draw();
    //�̗�
    m_pHpParam->Draw();
}



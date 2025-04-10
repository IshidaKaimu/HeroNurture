#include "CNatureScene.h"
#if _DEBUG
#include "ImGui\ImGuiManager\ImGuiManager.h"
#endif
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Light\LightManager\CLightManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Utility\CUtility.h"
#include "Rank\CRank.h"
#include "Sound\CSoundManager.h"
//�萔�̖��O���
using namespace Constant_NatureScene;


CNatureScene::CNatureScene()
    : m_pCamera      ( &CCameraManager::GetInstance() )
    , m_pHero        ( &CHeroManager::GetInstance() )
    , m_Name         ()
    , m_pGround      ()
    , m_pSky         ()
    , m_pParamBack   ()
    , m_pPowerTraning()
    , m_pMagicTraning()
    , m_pSpeedTraning()
    , m_pHpTraning   ()
    , m_pRest        ()
    , m_pStaminaGage ()
    , m_pStaminaBack ()
    , m_pStaminaFrame()
    , m_pTurnBack    ()
    , m_GageWidth    ( CSceneManager::GetInstance()->GetStaminaWidth() )
    , m_pJson        ()
    , m_ParamWriter  ()
    , m_ParamData    ()
{
}

CNatureScene::~CNatureScene()
{
}

void CNatureScene::Create()
{
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃C���X�^���X����
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        m_pHero->CreateHero(CHeroManager::Yui);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        m_pHero->CreateHero(CHeroManager::Kaito);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //----�X�^�e�B�b�N���b�V���I�u�W�F�N�g----
    //�n��
    m_pGround = std::make_unique<CGround>();
    //�X�J�C�{�b�N�X
    m_pSky    = std::make_unique<CSky>();

    //----UI�I�u�W�F�N�g----
    //�p�����[�^�̔w�i
    m_pParamBack = std::make_unique<CUIObject>();
    //�e��g���[�j���OUI
    m_pPowerTraning = std::make_unique<CUIObject>();
    m_pMagicTraning = std::make_unique<CUIObject>();
    m_pSpeedTraning = std::make_unique<CUIObject>();
    m_pHpTraning    = std::make_unique<CUIObject>();
    m_pRest         = std::make_unique<CUIObject>();

    //�琬�֘A�̃V�[���ŋ��ʂ��ĕ\������UI�̃C���X�^���X����
    CreateNatureUI(m_pStaminaGage,m_pStaminaBack,m_pStaminaFrame,m_pTurnBack);
}

void CNatureScene::Releace()
{
    //----�j��----
    //�J����
    m_pCamera = nullptr;
    //�q�[���[�}�l�[�W���[
    m_pHero   = nullptr;
}

void CNatureScene::LoadData()
{   
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃��b�V���f�[�^�̓ǂݍ���
    CHeroManager::GetInstance().LoadMeshData();

    CHeroManager::GetInstance().LoadParamData(m_ParamData);

    //�n�ʂ̃��b�V���f�[�^�ݒ�
    m_pGround->LoadData();

    //�p�����[�^�̔w�iUI�̃X�v���C�g�ݒ�
    m_pParamBack->AttachSprite(CUIManager::GetSprite(CUIManager::ParamList));
    //�e��g���[�j���OUI�̃X�v���C�g�ݒ�
    m_pPowerTraning->AttachSprite(CUIManager::GetSprite(CUIManager::PowerTraning));
    m_pMagicTraning->AttachSprite(CUIManager::GetSprite(CUIManager::MagicTraning));
    m_pSpeedTraning->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedTraning));
    m_pHpTraning   ->AttachSprite(CUIManager::GetSprite(CUIManager::HpTraning));
    m_pRest        ->AttachSprite(CUIManager::GetSprite(CUIManager::Rest));

    //�X�^�~�i�Q�[�W��UI�̃X�v���C�g�ݒ�
    LoadNatureUI(m_pStaminaGage, m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
}

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
    m_Light.Position   = D3DXVECTOR3(LIGHT_POS);
    //����
    m_Light.vDirection = D3DXVECTOR3(LIGHT_DIR); 
   
    //----�p�����[�^�̒l������UI�̏����ݒ�----
    //�p�����[�^�̔w�i
    UIInit(m_pParamBack, PARAMBACK_POSX, PARAMBACK_POSY, 0, PARAMBACK_SCALE, 0);
    //�e��g���[�j���O
    UIInit(m_pPowerTraning, TRANING_POSX, TRANING_POSY, 0, TRANING_SCALE, 0);
    UIInit(m_pMagicTraning, TRANING_POSX, TRANING_POSY, TRANING_INTERVAL, TRANING_SCALE, 1);
    UIInit(m_pSpeedTraning, TRANING_POSX, TRANING_POSY, TRANING_INTERVAL, TRANING_SCALE, 2);
    UIInit(m_pHpTraning,    TRANING_POSX, TRANING_POSY, TRANING_INTERVAL, TRANING_SCALE, 3);
    UIInit(m_pRest, TRANING_POSX, TRANING_POSY, TRANING_INTERVAL, TRANING_SCALE, 4);

    //�琬�֘A�̃V�[���ŋ��ʂ�UI�̏�����
    InitNatureUI(m_pStaminaGage,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
}

void CNatureScene::Update()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_NatureHeroSelect);

    //�琬BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Nature);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Nature, 40);

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̍X�V
    m_pHero->Update();

    //�L�[�}�l�[�W���[�̍X�V����
    CKeyManager::GetInstance().Update();

    //�J�[�\���̈ړ�
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //�I��SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        //�L�[���͂őI����i�߂�
        if (m_SelectNo < CHeroManager::enTraningList::Max_T-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        //�I��SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 4; }
    }

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃A�j���[�V����
    m_pHero->NatureAnimation(m_SelectNo);


    //�g���[�j���O�̌���
    if (KeyMng->IsDown(VK_RETURN) && !m_SceneTransitionFlg)
    {
        //����SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        //�I�����̈ʒu�ɉ������g���[�j���O���Z�b�g
        switch (m_SelectNo)
        {
        case 0:  m_pHero->SetTraning(CHeroManager::PowerTraining); break;
        case 1:  m_pHero->SetTraning(CHeroManager::MagicTraining); break;
        case 2:  m_pHero->SetTraning(CHeroManager::SpeedTraining); break;
        case 3:  m_pHero->SetTraning(CHeroManager::HpTraining); break;
        case 4:  m_pHero->SetTraning(CHeroManager::Rest); break;
        }
        //�p�����[�^����
        SelectTraning();

        m_SceneTransitionFlg = true;
    }

    if (SceneMng->GetRemainingTurn() <= 0) 
    {
        m_SceneTransitionFlg = true;
    }

    if (m_SceneTransitionFlg && FadeOut())
    {
        if (SceneMng->GetRemainingTurn() > 0)
        {
            SceneMng->LoadCreate(CSceneManager::Training);
        }
        else
        {
            SceneMng->LoadCreate(CSceneManager::NatureResult);
        }
    }

    //�f�o�b�O����
    Debug();
}

void CNatureScene::Draw()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�J�����̍X�V����
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̕`��
    m_pHero->Draw();

    //�n�ʃN���X�̕`��
    m_pGround->Draw();

    //�[�x�𖳎�����
    SceneMng->GetDx11()->SetDepth(false);

    //�琬�֘A�V�[���ŋ��ʂ�UI�̕`��
    DrawNatureUI(m_pStaminaGage, m_pStaminaBack, m_pStaminaFrame,m_pTurnBack);

    //�e�g���[�j���O�̕`��
    DrawTraning();

    //�e�p�����[�^UI�̕`��
    DrawParam();

    //�[�x��߂�
    SceneMng->GetDx11()->SetDepth(true);
}

void CNatureScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef _DEBUG 
    ImGui::Begin(JAPANESE("�p�����[�^"));
    ImGui::Text(JAPANESE("�ؗ�:%f"), m_pHero->GetParam().Power);
    ImGui::Text(JAPANESE("����:%f"), m_pHero->GetParam().Magic);
    ImGui::Text(JAPANESE("�f����:%f"), m_pHero->GetParam().Speed);
    ImGui::Text(JAPANESE("�̗�:%f"), m_pHero->GetParam().Hp);
    ImGui::Text(JAPANESE("�X�^�~�i:%f"), m_pHero->GetStamina());
    ImGui::Text(JAPANESE("�X�^�~�i�̕�:%f"), CSceneManager::GetInstance()->GetStaminaWidth());
    ImGui::End();

    ImGui::Begin(JAPANESE("�g���[�j���O�I����"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("�ؗ�")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("����")); }
    if (m_SelectNo == 2) { ImGui::Text(JAPANESE("�f����")); }
    if (m_SelectNo == 3) { ImGui::Text(JAPANESE("�̗�")); }
    if (m_SelectNo == 4) { ImGui::Text(JAPANESE("�x��")); }
    ImGui::End();
#endif

    //���C�g�}�l�[�W���[
#ifdef DEBUG 
    CLightManager::GetInstance().Debug();
#endif
}

//�琬�֘AUI�̃C���X�^���X����
void CNatureScene::CreateNatureUI(
    std::unique_ptr<CUIObject>& gage, 
    std::unique_ptr<CUIObject>& back, 
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //�X�^�~�i�Q�[�W
    gage = std::make_unique<CUIObject>();
    //�Q�[�W�w�i
    back = std::make_unique<CUIObject>();
    //�Q�[�W�g
    frame = std::make_unique<CUIObject>();
    //�^�[���w�i
    turnback = std::make_unique<CUIObject>();
}
//�琬�֘AUI�̃X�v���C�g�f�[�^�̓ǂݍ���
void CNatureScene::LoadNatureUI(
    std::unique_ptr<CUIObject>& gage, 
    std::unique_ptr<CUIObject>& back, 
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //�X�^�~�i�Q�[�W
    gage->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaGage));
    //�Q�[�W�w�i
    back->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaBack));
    //�Q�[�W�g
    frame->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaFrame));
    //�^�[�����w�i
    turnback->AttachSprite(CUIManager::GetSprite(CUIManager::TurnBack));
}
//�琬�֘AUI�̏�����
void CNatureScene::InitNatureUI(
    std::unique_ptr<CUIObject>& gage,
    std::unique_ptr<CUIObject>& back,
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //�ǂݍ��݂�����ł���Ȃ�
    if (!CSceneManager::GetInstance()->GetIsDataLoaded())
    {
        //�^�[�����EHP�̒l�̏�����
        //�^�[����
        CSceneManager::GetInstance()->InitTurn();
        gage->SetWidth(1.0f);
        //�X�^�~�i�̏�����
        m_pHero->InitStamina();
    }
    else
    {
        //�X�^�~�i�Ɍ�����̒l���Z�b�g
        m_pHero->SetStamina(m_pHero->GetAfterStamina());
        //���݂̃X�^�~�i�����擾���A�ݒ肷��
        gage->SetWidth(CSceneManager::GetInstance()->GetStaminaWidth());
    }

    //�X�^�~�i�Q�[�W
    gage->SetScale(BASIC_SCALE);            
    gage->SetPosition(STAMINA_POS);  

    //�X�^�~�i�Q�[�W�w�i
    back->SetScale(BASIC_SCALE);              
    back->SetPosition(STAMINA_POS);  
    back->SetDisplay(BASIC_DISPLAY.x, BASIC_DISPLAY.y);         
    
    //�X�^�~�i�Q�[�W�g
    frame->SetScale(BASIC_SCALE);             
    frame->SetPosition(STAMINAFRAME_POS);   
    frame->SetDisplay(BASIC_DISPLAY.x, BASIC_DISPLAY.y);

    //�^�[�����w�i
    turnback->SetScale(BASIC_SCALE);          
    turnback->SetPosition(TURNBACK_POS);  
    turnback->SetDisplay(BASIC_DISPLAY.x, BASIC_DISPLAY.y);
}
//�`��
void CNatureScene::DrawNatureUI(
    std::unique_ptr<CUIObject>& gage,
    std::unique_ptr<CUIObject>& back,
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //�X�^�~�i�Q�[�W�̃A�j���[�V����
    StaminaGageAnim();
    //�^�[�����w�i
    turnback->Draw();
    //�Q�[�W�g
    frame->Draw();
    //�Q�[�W�w�i
    back->Draw();
    //�X�^�~�i�Q�[�W
    gage->Draw();
    //�c��^�[�����̕`��
    DrawRemainingTurn();
}

//�e�q�[���[�̃f�[�^�ǂݍ���
void CNatureScene::LoadHeroData( const std::string& heroname )
{
    //�ǂݍ��ރt�@�C���̃p�X
    //����̓ǂݍ��ݎ��ɓǂݍ��ޏ����X�e�[�^�X�t�@�C��
    std::string InitFilePath = "Data\\Hero\\HeroData";
    //�p�����[�^���X�V���ɓǂݍ��ރt�@�C��
    std::string ParamFilePath = "Data\\Hero\\Parameter\\" + heroname;

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

//�g���[�j���O�I������
void CNatureScene::SelectTraning()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�X�V�O�̃p�����[�^��ۑ�
     m_pHero->SetBeforeParam(m_pHero->GetParam());
    //�X�V�O�̃X�^�~�i��ۑ�
     m_pHero->SetBeforeStamina(m_pHero->GetStamina());

    //���ꂼ��̃p�����[�^�̑���
    switch (m_pHero->GetTraining())
    {
    case::CHeroManager::PowerTraining: m_pHero->PowerUp(m_pHero->GetStamina()); break; //�ؗ�
    case::CHeroManager::MagicTraining: m_pHero->MagicUp(m_pHero->GetStamina()); break; //����
    case::CHeroManager::SpeedTraining: m_pHero->SpeedUp(m_pHero->GetStamina()); break; //�f����
    case::CHeroManager::HpTraining: m_pHero->HpUp(m_pHero->GetStamina()); break;       //�̗�
    case::CHeroManager::Rest: SceneMng->SetRestFlag(true); break;                      //�x��
    }

    //�X�^�~�i�̌����܂��͉�
    //�x���t���O�������Ă��Ȃ���Ό���
    if (!SceneMng->GetRestFlag()) { m_pHero->ReduceStamina(); }
    else { m_pHero->StaminaRecovery(); }

    //�X�V��p�����[�^�̕ۑ�
    SaveParam();

    //����̂ݓǂݍ��ނ��̂�ǂݍ��܂Ȃ�����
    CSceneManager::GetInstance()->SetIsDataLoaded(true);

}

//�e��g���[�j���OUI�����ݒ�
void CNatureScene::UIInit(std::unique_ptr<CUIObject>& ui, float x, float y, float interval, D3DXVECTOR3 scale, int no)
{
    //�ʒu
    ui->SetPosition(x + (interval * no), y, 0.0f);
    //�g�k
    ui->SetScale(scale);
    //���l
    ui->SetAlpha(1.0f);
    //���A����
    ui->SetDisplay(1.0f, 1.0f);
}


//�q�[���[���Ƃ̃p�����[�^��������
void CNatureScene::SaveParam()
{
    //�g���[�j���O���s���Ƀp�����[�^�����������ރt�@�C���̊K�w
    std::string ParamFileHierarchy = "Data\\Hero\\Parameter\\";
    //�Z�b�g���ꂽ�q�[���[�̃p�����[�^���̏�������
    m_pJson->SaveNatureData(m_pHero->GetHeroName(), m_ParamWriter, ParamFileHierarchy);
}

//�e��p�����[�^�̕`��
void CNatureScene::DrawParam()
{
    WriteText* Text = WriteText::GetInstance();
    CUtility* Utility = &CUtility::GetInstance();

    //----�e��p�����[�^��UI�`��(�w�i,�l,�����N)----
    //�w�i
    m_pParamBack->Draw();
    //�ؗ�
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Power)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Power,CORRECTION_DIGIT,PARAMVALUE_POSX, PARAMVALUE_POSY));
    CRank::GetInstance().DrawRank(m_pHero->GetParam().Power, 2, RANK_POSX, RANK_POSY);
    //����
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Magic)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Magic, CORRECTION_DIGIT, PARAMVALUE_POSX + PARAMVALUE_INTERVAL, PARAMVALUE_POSY));
    CRank::GetInstance().DrawRank(m_pHero->GetParam().Magic, 2, RANK_POSX + RANK_INTERVAL, RANK_POSY);
    //�f����
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Speed)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Speed, CORRECTION_DIGIT, PARAMVALUE_POSX + (PARAMVALUE_INTERVAL * 2), PARAMVALUE_POSY));
    CRank::GetInstance().DrawRank(m_pHero->GetParam().Speed, 2, RANK_POSX + (RANK_INTERVAL * 2), RANK_POSY);
    //�̗�
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Hp)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Hp, CORRECTION_DIGIT, PARAMVALUE_POSX + (PARAMVALUE_INTERVAL * 3), PARAMVALUE_POSY));
    CRank::GetInstance().DrawRank(m_pHero->GetParam().Hp, 2, RANK_POSX + (RANK_INTERVAL * 3), RANK_POSY);
}

//�e��g���[�j���O�̕`��
void CNatureScene::DrawTraning()
{
    //�I�����ꂽ�Ƃ����ꂼ��̈ʒu���グ��ϐ�
    float PosUp = 20.0f;

    //�ؗ̓g���[�j���O�I����
    if (m_SelectNo == 0) { m_pPowerTraning->SetPositionY(TRANING_POSY - PosUp); }
    else { m_pPowerTraning->SetPositionY(TRANING_POSY); }
    //���̓g���[�j���O�I����
    if (m_SelectNo == 1) { m_pMagicTraning->SetPositionY(TRANING_POSY - PosUp); }
    else { m_pMagicTraning->SetPositionY(TRANING_POSY); }
    //�f�����g���[�j���O�I����
    if (m_SelectNo == 2) { m_pSpeedTraning->SetPositionY(TRANING_POSY  - PosUp); }
    else { m_pSpeedTraning->SetPositionY(TRANING_POSY); }
    //�̗̓g���[�j���O�I����
    if (m_SelectNo == 3) { m_pHpTraning->SetPositionY(TRANING_POSY - PosUp); }
    else { m_pHpTraning->SetPositionY(TRANING_POSY); }
    //�x���I����
    if (m_SelectNo == 4) { m_pRest->SetPositionY(TRANING_POSY - PosUp); }
    else { m_pRest->SetPositionY(TRANING_POSY); }

    m_pPowerTraning->Draw();
    m_pMagicTraning->Draw();
    m_pSpeedTraning->Draw();
    m_pHpTraning->Draw();
    m_pRest->Draw();
}

//�c��^�[�����̕`��
void CNatureScene::DrawRemainingTurn()
{
    WriteText* Text = WriteText::GetInstance();
    CUtility* Utility = &CUtility::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //������wstring�^�ɕϊ�
    std::wstring Turn = std::to_wstring(CSceneManager::GetInstance()->GetRemainingTurn());

    //�c��^�[�����̕`��
    Text->Draw_Text(L"�c��", WriteText::TurnText, D3DXVECTOR2(10.0f,-20.0f));
    Text->Draw_Text(Turn, WriteText::Turn, Utility->PosCorrection(SceneMng->GetRemainingTurn(),2,180.0f,-10.0f));
    Text->Draw_Text(L"�^�[��", WriteText::TurnText, D3DXVECTOR2(240.0f, -20.0f));
}


//�X�^�~�i�Q�[�W�̃A�j���[�V����
void CNatureScene::StaminaGageAnim()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�Q�[�W���̊m�F
    float GageScale = 1.0f * m_pHero->GetStamina() / STAMINA_MAX;

    //�������
    if (GageScale < m_GageWidth) { m_GageWidth -= 0.01f; }
    //�Ⴏ���
    if (GageScale > m_GageWidth){ m_GageWidth += 0.01f; }

    //���݂̃Q�[�W�����V�[���}�l�[�W���̕ϐ��ɑ��
    CSceneManager::GetInstance()->SetStaminaWidth(m_GageWidth);

    //�X�^�~�i�Q�[�W�̕�������ݒ�
    if (SceneMng->GetIsDataLoaded()) {
        m_pStaminaGage->SetDisplay(m_GageWidth, 1.0f);
    }
    else
    {
        //�s���R�ȃQ�[�W�̓������Ȃ���
        m_pStaminaGage->SetDisplay(1.0f, 1.0f);
    }
}

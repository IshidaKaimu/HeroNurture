#include "CNurtureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Light\LightManager\CLightManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Utility\CUtility.h"
#include "Rank\CRank.h"
#include "Sound\CSoundManager.h"

//�萔�̖��O���
using namespace Constant_NurtureScene;


CNurtureScene::CNurtureScene()
    : m_pCamera      ( &CCameraManager::GetInstance() )
    , m_Name         ()
    , m_pGround      ()
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
    , m_pSafeBack    ()
    , m_pAnxietyBack ()
    , m_pDangerBack  ()
    , m_GageWidth    ( CNurtureManager::GetInstance().GetStaminaWidth() )
    , m_pJson        ()
    , m_ParamWriter  ()
    , m_ParamData    ()
{
}

CNurtureScene::~CNurtureScene()
{
}

void CNurtureScene::Create()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃C���X�^���X����
    switch (HeroMng->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        HeroMng->CreateHero(CHeroManager::Yui);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        HeroMng->CreateHero(CHeroManager::Kaito);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //----�X�^�e�B�b�N���b�V���I�u�W�F�N�g----
    //�n��
    m_pGround = std::make_unique<CGround>();

    //----UI�I�u�W�F�N�g----
    //�p�����[�^�̔w�i
    m_pParamBack = std::make_unique<CUIObject>();
    //�e��g���[�j���OUI
    m_pPowerTraning = std::make_unique<CUIObject>();
    m_pMagicTraning = std::make_unique<CUIObject>();
    m_pSpeedTraning = std::make_unique<CUIObject>();
    m_pHpTraning    = std::make_unique<CUIObject>();
    m_pRest         = std::make_unique<CUIObject>();
    //���s���w�i
    m_pSafeBack     = std::make_unique<CUIObject>();
    m_pAnxietyBack  = std::make_unique<CUIObject>();
    m_pDangerBack   = std::make_unique<CUIObject>();

    //�琬�֘A�̃V�[���ŋ��ʂ��ĕ\������UI�̃C���X�^���X����
    CreateNurtureUI(m_pStaminaGage,m_pStaminaBack,m_pStaminaFrame,m_pTurnBack);
}

void CNurtureScene::Releace()
{
    //----�j��----
    //�J����
    m_pCamera = nullptr;
}

void CNurtureScene::LoadData()
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
    //�e���s���w�i�̃X�v���C�g�ݒ�
    m_pSafeBack->AttachSprite(CUIManager::GetSprite(CUIManager::Safe));
    m_pAnxietyBack->AttachSprite(CUIManager::GetSprite(CUIManager::Anxiety));
    m_pDangerBack->AttachSprite(CUIManager::GetSprite(CUIManager::Danger));

    //�X�^�~�i�Q�[�W��UI�̃X�v���C�g�ݒ�
    LoadNurtureUI(m_pStaminaGage, m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
}

void CNurtureScene::Initialize()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̏�����
    HeroMng->Initialize();

    //�e�q�[���[�̃J�����ʒu�A�J�����̒����_�̐ݒ�
    switch (HeroMng->GetSelectHero())
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
    UIInit(m_pParamBack, PARAMBACK_POS, 0, PARAMBACK_SCALE, 0);
    //�e��g���[�j���O
    UIInit(m_pPowerTraning, TRANING_POS, 0, TRANING_SCALE, 0);                //�ؗ�
    UIInit(m_pMagicTraning, TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 1); //����
    UIInit(m_pSpeedTraning, TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 2); //�f����
    UIInit(m_pHpTraning,    TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 3); //�̗�
    UIInit(m_pRest,         TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 4); //�x��
    //�e���s���w�i
    FailureRateBackInit(m_pSafeBack,D3DXVECTOR3(20.0f,400.0f,0.0f));
    FailureRateBackInit(m_pAnxietyBack,D3DXVECTOR3(20.0f,400.0f,0.0f));
    FailureRateBackInit(m_pDangerBack,D3DXVECTOR3(20.0f,400.0f,0.0f));


    //�琬�֘A�̃V�[���ŋ��ʂ�UI�̏�����
    InitNurtureUI(m_pStaminaGage,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
}

void CNurtureScene::Update()
{
    CKeyManager*     KeyMng     = &CKeyManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�h�I����ʂ�BGM��~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_NurtureHeroSelect);

    //�琬BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Nurture);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Nurture, 40);

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̍X�V
    HeroMng->Update();

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
    HeroMng->NurtureAnimation(m_SelectNo);


    //�g���[�j���O�̌���
    if (KeyMng->IsDown(VK_RETURN) && !m_SceneTransitionFlg)
    {
        //����SE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        m_SceneTransitionFlg = true;

        //�I�����̈ʒu�ɉ������g���[�j���O���Z�b�g
        switch (m_SelectNo)
        {
        case 0:  HeroMng->SetTraning(CHeroManager::PowerTraining); break;
        case 1:  HeroMng->SetTraning(CHeroManager::MagicTraining); break;
        case 2:  HeroMng->SetTraning(CHeroManager::SpeedTraining); break;
        case 3:  HeroMng->SetTraning(CHeroManager::HpTraining); break;
        case 4:  HeroMng->SetTraning(CHeroManager::Rest); break;
        }

    }

    if (NurtureMng->GetRemainingTurn() <= 0) 
    {
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h���I�������
    if (m_SceneTransitionFlg && FadeOut())
    {
        if (NurtureMng->GetRemainingTurn() > 0)
        {
            //�p�����[�^����
            SelectTraning();
            SceneMng->LoadCreate(CSceneManager::Training);
        }
        else
        {
            SceneMng->LoadCreate(CSceneManager::NurtureResult);
        }
    }

    //�f�o�b�O����
    Debug();
}

void CNurtureScene::Draw()
{
    CHeroManager*  HeroMng  = &CHeroManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    WriteText*     Text     = WriteText::GetInstance();

    //�J�����̍X�V����
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̕`��
    HeroMng->Draw();

    //�n�ʃN���X�̕`��
    m_pGround->Draw();

    //��̕`��
    DrawSky();

    //�[�x�𖳎�����
    SceneMng->GetDx11()->SetDepth(false);

    //�琬�֘A�V�[���ŋ��ʂ�UI�̕`��
    DrawNurtureUI(m_pStaminaGage, m_pStaminaBack, m_pStaminaFrame,m_pTurnBack);

    //�e�g���[�j���O�̕`��
    DrawTraning();

    //�e�p�����[�^UI�̕`��
    DrawParam();

    //���s���̎擾
    int FailureRate = 100 - HeroMng->GetSuccessRate(HeroMng->GetStamina());
    //���s���ɉ������w�i�̕`��
    if (FailureRate <= SAFE) { m_pSafeBack->Draw(); }
    if (FailureRate > SAFE && FailureRate <= ANXIETY) { m_pAnxietyBack->Draw(); }
    if (FailureRate > ANXIETY) { m_pDangerBack->Draw(); }
    //�u���s���v�e�L�X�g�`��
    Text->Draw_Text(L"���s��", WriteText::Select, D3DXVECTOR2(FAILURETEXT_POS));
    //���s���̕`��
    Text->Draw_Text(std::to_wstring(FailureRate) + L"%", WriteText::Select, D3DXVECTOR2(FAILURERATE_POS));

    //�[�x��߂�
    SceneMng->GetDx11()->SetDepth(true);
}

void CNurtureScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef DEBUG 
    ImGui::Begin(JAPANESE("�p�����[�^"));
    ImGui::Text(JAPANESE("�ؗ�:%f"), HeroMng->GetParam().Power);
    ImGui::Text(JAPANESE("����:%f"), HeroMng->GetParam().Magic);
    ImGui::Text(JAPANESE("�f����:%f"), HeroMng->GetParam().Speed);
    ImGui::Text(JAPANESE("�̗�:%f"), HeroMng->GetParam().Hp);
    ImGui::Text(JAPANESE("�X�^�~�i:%f"), HeroMng->GetStamina());
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
void CNurtureScene::CreateNurtureUI(
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
void CNurtureScene::LoadNurtureUI(
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
void CNurtureScene::InitNurtureUI(
    std::unique_ptr<CUIObject>& gage,
    std::unique_ptr<CUIObject>& back,
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();

    //�ǂݍ��݂�����ł���Ȃ�
    if (!NurtureMng->GetIsDataLoaded())
    {
        //�^�[�����EHP�̒l�̏�����
        //�^�[����
        NurtureMng->InitTurn();
        gage->SetWidth(1.0f);
        //�X�^�~�i�̏�����
        HeroMng->InitStamina();
    }
    else
    {
        //�X�^�~�i�Ɍ�����̒l���Z�b�g
        HeroMng->SetStamina(HeroMng->GetAfterStamina());
        //���݂̃X�^�~�i�����擾���A�ݒ肷��
        gage->SetWidth(NurtureMng->GetStaminaWidth());
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
void CNurtureScene::DrawNurtureUI(
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
void CNurtureScene::LoadHeroData( const std::string& heroname )
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //�ݒ肳��Ă��郆�[�U�[���̎擾
    std::string UserName = SceneMng->GetStringName();

    //�ǂݍ��ރt�@�C���̃p�X
    //����̓ǂݍ��ݎ��ɓǂݍ��ޏ����X�e�[�^�X�t�@�C��
    std::string InitFilePath = "Data\\Acount\\" + UserName + "\\HeroData";
    //�p�����[�^���X�V���ɓǂݍ��ރt�@�C��
    std::string ParamFilePath = "Data\\Acount\\" + UserName + "\\Parameter\\" + heroname;

    //json�ɕۑ����ꂽ�f�[�^�̓ǂݍ���
    //�ǂݍ��݉񐔂ɉ����ēǂݍ��ރt�@�C����ς���
    if (!NurtureMng->GetIsDataLoaded())
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
void CNurtureScene::SelectTraning()
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();


    //�X�V�O�̃p�����[�^��ۑ�
     HeroMng->SetBeforeParam(HeroMng->GetParam());
    //�X�V�O�̃X�^�~�i��ۑ�
     HeroMng->SetBeforeStamina(HeroMng->GetStamina());

    //���ꂼ��̃p�����[�^�̑���
    switch (HeroMng->GetTraining())
    {
    case::CHeroManager::PowerTraining: HeroMng->PowerUp(HeroMng->GetStamina()); break; //�ؗ�
    case::CHeroManager::MagicTraining: HeroMng->MagicUp(HeroMng->GetStamina()); break; //����
    case::CHeroManager::SpeedTraining: HeroMng->SpeedUp(HeroMng->GetStamina()); break; //�f����
    case::CHeroManager::HpTraining: HeroMng->HpUp(HeroMng->GetStamina()); break;       //�̗�
    case::CHeroManager::Rest: NurtureMng->SetRestFlag(true); break;                      //�x��
    }

    //�X�^�~�i�̌����܂��͉�
    //�x���t���O�������Ă��Ȃ���Ό���
    if (!NurtureMng->GetRestFlag()) { HeroMng->ReduceStamina(); }
    else { HeroMng->StaminaRecovery(); }

    //�X�V��p�����[�^�̕ۑ�
    SaveParam();

    //����̂ݓǂݍ��ނ��̂�ǂݍ��܂Ȃ�����
    NurtureMng->SetIsDataLoaded(true);

}

//�e��g���[�j���OUI�����ݒ�
void CNurtureScene::UIInit(std::unique_ptr<CUIObject>& ui, D3DXVECTOR3 pos, float interval, D3DXVECTOR3 scale, int no)
{
    //�ʒu
    ui->SetPosition(pos.x + (interval * no), pos.y, 0.0f);
    //�g�k
    ui->SetScale(scale);
    //���l
    ui->SetAlpha(1.0f);
    //���A����
    ui->SetDisplay(1.0f, 1.0f);
}

//���s���w�i�̏����ݒ�
void CNurtureScene::FailureRateBackInit(std::unique_ptr<CUIObject>& back, D3DXVECTOR3 pos)
{
    back->SetPosition(FAILUREBACK_POS);
    back->SetScale(FAILUREBACK_SCALE);
    back->SetAlpha(FAILUREBACK_ALPHA);
    back->SetDisplay(FAILUREBACK_DISP.x, FAILUREBACK_DISP.y);
}


//�q�[���[���Ƃ̃p�����[�^��������
void CNurtureScene::SaveParam()
{
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    CHeroManager*  HeroMng  = &CHeroManager::GetInstance();

    //�ݒ肳��Ă��郆�[�U�[���̎擾
    std::string UserName = SceneMng->GetStringName();

    //�g���[�j���O���s���Ƀp�����[�^�����������ރt�@�C���̊K�w
    std::string ParamFileHierarchy = "Data\\Acount\\" + UserName + "\\Parameter\\";
    //�Z�b�g���ꂽ�q�[���[�̃p�����[�^���̏�������
    m_pJson->SaveNurtureData(HeroMng->GetSelectHeroName(), m_ParamWriter, ParamFileHierarchy);
}

//�e��p�����[�^�̕`��
void CNurtureScene::DrawParam()
{
    WriteText*    Text    = WriteText::GetInstance();
    CUtility*     Utility = &CUtility::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //----�e��p�����[�^��UI�`��(�w�i,�l,�����N)----
    //�w�i
    m_pParamBack->Draw();
    //�ؗ�
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Power)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Power,CORRECTION_DIGIT,PARAMVALUE_POS));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Power, 2, RANK_POS);
    //����
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Magic)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Magic, CORRECTION_DIGIT, D3DXVECTOR2(PARAMVALUE_POS.x + PARAMVALUE_INTERVAL, PARAMVALUE_POS.y)));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Magic, 2, D3DXVECTOR2(RANK_POS.x + RANK_INTERVAL, RANK_POS.y));
    //�f����
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Speed)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Speed, CORRECTION_DIGIT, D3DXVECTOR2(PARAMVALUE_POS.x + (PARAMVALUE_INTERVAL * 2), PARAMVALUE_POS.y)));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Speed, 2, D3DXVECTOR2(RANK_POS.x + (RANK_INTERVAL * 2), RANK_POS.y));
    //�̗�
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Hp)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Hp, CORRECTION_DIGIT, D3DXVECTOR2(PARAMVALUE_POS.x + (PARAMVALUE_INTERVAL * 3), PARAMVALUE_POS.y)));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Hp, 2, D3DXVECTOR2(RANK_POS.x + (RANK_INTERVAL * 3), RANK_POS.y));
}

//�e��g���[�j���O�̕`��
void CNurtureScene::DrawTraning()
{
    //�I�����ꂽ�Ƃ����ꂼ��̈ʒu���グ��ϐ�
    float PosUp = 20.0f;

    //�ؗ̓g���[�j���O�I����
    if (m_SelectNo == 0) { m_pPowerTraning->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pPowerTraning->SetPositionY(TRANING_POS.y); }
    //���̓g���[�j���O�I����
    if (m_SelectNo == 1) { m_pMagicTraning->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pMagicTraning->SetPositionY(TRANING_POS.y); }
    //�f�����g���[�j���O�I����
    if (m_SelectNo == 2) { m_pSpeedTraning->SetPositionY(TRANING_POS.y  - PosUp); }
    else { m_pSpeedTraning->SetPositionY(TRANING_POS.y); }
    //�̗̓g���[�j���O�I����
    if (m_SelectNo == 3) { m_pHpTraning->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pHpTraning->SetPositionY(TRANING_POS.y); }
    //�x���I����
    if (m_SelectNo == 4) { m_pRest->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pRest->SetPositionY(TRANING_POS.y); }

    m_pPowerTraning->Draw();
    m_pMagicTraning->Draw();
    m_pSpeedTraning->Draw();
    m_pHpTraning->Draw();
    m_pRest->Draw();
}

//�c��^�[�����̕`��
void CNurtureScene::DrawRemainingTurn()
{
    WriteText*       Text       = WriteText::GetInstance();
    CUtility*        Utility    = &CUtility::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //������wstring�^�ɕϊ�
    std::wstring Turn = std::to_wstring(NurtureMng->GetRemainingTurn());

    //�c��^�[�����̕`��
    Text->Draw_Text(L"�c��", WriteText::TurnText, REMAININGTEXT_POS);
    Text->Draw_Text(Turn, WriteText::Turn, Utility->PosCorrection(NurtureMng->GetRemainingTurn(),2,TURN_POS));
    Text->Draw_Text(L"�^�[��", WriteText::TurnText, TURNTEXT_POS);
}


//�X�^�~�i�Q�[�W�̃A�j���[�V����
void CNurtureScene::StaminaGageAnim()
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();


    //�Q�[�W���̊m�F
    float GageScale = 1.0f * HeroMng->GetStamina() / STAMINA_MAX;

    //�������
    if (GageScale < m_GageWidth) { m_GageWidth -= 0.01f; }
    //�Ⴏ���
    if (GageScale > m_GageWidth){ m_GageWidth += 0.01f; }

    //���݂̃Q�[�W�����V�[���}�l�[�W���̕ϐ��ɑ��
    NurtureMng->SetStaminaWidth(m_GageWidth);

    //�X�^�~�i�Q�[�W�̕�������ݒ�
    if (NurtureMng->GetIsDataLoaded()) {
        m_pStaminaGage->SetDisplay(m_GageWidth, 1.0f);
    }
    else
    {
        //�s���R�ȃQ�[�W�̓������Ȃ���
        m_pStaminaGage->SetDisplay(1.0f, 1.0f);
    }
}
